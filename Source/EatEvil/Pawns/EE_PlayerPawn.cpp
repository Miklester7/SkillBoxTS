// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/EE_PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(AEE_PlayerPawnLog, All, All);

AEE_PlayerPawn::AEE_PlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.0167f;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AEE_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	check(PlayerController);

	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AEE_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEE_PlayerPawn::Move);

		EnhancedInputComponent->BindAction(ChangeZoomAction, ETriggerEvent::Started, this, &AEE_PlayerPawn::ZoomChange);
	}
}

void AEE_PlayerPawn::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AEE_PlayerPawn::ZoomChange(const FInputActionValue& Value)
{
	const auto bIsIncrease = Value.Get<FInputActionValue::Axis1D>();
	if (bIsIncrease == 0) return;

	if (bIsIncrease > 0)
	{
		CurrentIncrementValue += IncrementValue;
	}
	else if(bIsIncrease < 0)
	{
		CurrentIncrementValue -= IncrementValue;
	}
	if (!GetWorldTimerManager().IsTimerActive(ZoomChangeTimer))
	{
		GetWorldTimerManager().SetTimer(ZoomChangeTimer, this, &AEE_PlayerPawn::UpdateZoom, FrequencyOfChange, true);
	}
}

void AEE_PlayerPawn::UpdateZoom()
{
	if (CurrentIncrementValue > 0)
	{
		SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + IncrementStep, CameraMin, CameraMax);
		CurrentIncrementValue -= IncrementStep;
	}
	else if (CurrentIncrementValue < 0)
	{
		SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength - IncrementStep, CameraMin, CameraMax);
		CurrentIncrementValue += IncrementStep;
	}

	if (CurrentIncrementValue == 0 || SpringArmComponent->TargetArmLength == CameraMin || SpringArmComponent->TargetArmLength == CameraMax)
	{
		CurrentIncrementValue = 0;
		GetWorldTimerManager().ClearTimer(ZoomChangeTimer);
	}
}

void AEE_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector2D ViewportCenter = GetViewportCenter();
	const FVector2D MouseViewportPosition = GetMouseViewportPosition();
	if (MouseViewportPosition.IsZero()) return;

	const FVector Direction = CursorDistFromCenter(MouseViewportPosition - ViewportCenter, ViewportCenter);

	const FVector WorldDirection = UKismetMathLibrary::TransformDirection(GetActorTransform(), Direction);

	UE_LOG(AEE_PlayerPawnLog, Display, TEXT("WorldDirection:%s"), *WorldDirection.ToString());
	AddMovementInput(WorldDirection);
}

FVector2D AEE_PlayerPawn::GetViewportCenter()
{
	FInt32Point ViewportSize;
	PlayerController->GetViewportSize(ViewportSize.X, ViewportSize.Y);

	const FVector2D ReturnViewportSize{ static_cast<float>(ViewportSize.X),static_cast<float>(ViewportSize.Y) };
	return ReturnViewportSize / 2;
}

FVector2D AEE_PlayerPawn::GetMouseViewportPosition()
{
	FVector2D MousePosition;
	const bool GotMousePosition = PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

	return GotMousePosition ? MousePosition : FVector2D{ 0.f };
}

FVector AEE_PlayerPawn::CursorDistFromCenter(FVector2D SubtractionResult,FVector2D Center)
{
	const auto ValueX = FMath::Abs(SubtractionResult.X) - (Center - MoveDistance).X;
	const auto ValueY = FMath::Abs(SubtractionResult.Y) - (Center - MoveDistance).Y;

	const auto OffsetX = FMath::Max<float>(ValueX, 0);
	const auto OffsetY = FMath::Max<float>(ValueY, 0);

	const auto SignX = UKismetMathLibrary::SignOfFloat(SubtractionResult.X);
	const auto SignY = UKismetMathLibrary::SignOfFloat(SubtractionResult.Y);

	const auto Y = OffsetX / MoveDistance * SignX;
	const auto X = OffsetY / MoveDistance * SignY;

	return FVector(-X,Y,0.0);
}