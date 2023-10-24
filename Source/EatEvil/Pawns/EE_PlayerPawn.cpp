// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/EE_PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(AEE_PlayerPawnLog, All, All);

AEE_PlayerPawn::AEE_PlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.0167f;
}

void AEE_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	check(PlayerController);
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
