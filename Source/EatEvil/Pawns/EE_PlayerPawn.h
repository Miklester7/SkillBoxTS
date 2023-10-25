// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "EE_PlayerPawn.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class EATEVIL_API AEE_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	AEE_PlayerPawn();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	void Move(const FInputActionValue& Value);
	void ZoomChange(const FInputActionValue& Value);
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Movement")
	float MoveDistance{ 100.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeZoomAction;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneComponent;

private:
	FVector2D GetViewportCenter();
	FVector2D GetMouseViewportPosition();
	FVector CursorDistFromCenter(FVector2D SubtractionResult, FVector2D Center);

	void UpdateZoom();
private:
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	FTimerHandle ZoomChangeTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float CameraMin{ 300.f };

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float CameraMax{ 1200.f };

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float FrequencyOfChange{ 0.0167f };

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float IncrementValue{ 100.f };

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float IncrementStep{ 1.f };

	float CurrentIncrementValue{ 0.f };
};
