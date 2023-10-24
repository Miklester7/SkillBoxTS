// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EE_PlayerPawn.generated.h"

UCLASS()
class EATEVIL_API AEE_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	AEE_PlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Movement")
	float MoveDistance{ 100.f };

private:
	FVector2D GetViewportCenter();
	FVector2D GetMouseViewportPosition();
	FVector CursorDistFromCenter(FVector2D SubtractionResult, FVector2D Center);

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
};
