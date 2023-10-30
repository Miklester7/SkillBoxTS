// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "EE_PlayerController.generated.h"

class AEE_DefaultPlaceInteractActor;

UCLASS()
class AEE_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEE_PlayerController();

	void AddPlaceInteractActor(AEE_DefaultPlaceInteractActor* Actor);

	bool GetAFKPlayer() { return AFKPlayer; }

	void SetAFKPlayer(bool Value) { AFKPlayer = Value; }
protected:
	virtual void BeginPlay();

private:
	UPROPERTY()
	TObjectPtr<AEE_DefaultPlaceInteractActor> LastPlaceInteractActor;

	void TargetUpdate(AEE_DefaultPlaceInteractActor* Actor);

	bool AFKPlayer{ false };
	FTimerHandle RunSequenceTimer;

	void RunSequence();
};


