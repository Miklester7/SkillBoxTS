// Copyright Epic Games, Inc. All Rights Reserved.

#include "EE_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Actors/EE_DefaultPlaceInteractActor.h"


AEE_PlayerController::AEE_PlayerController()
{
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
}

void AEE_PlayerController::AddPlaceInteractActor(AEE_DefaultPlaceInteractActor* Actor)
{
	Actor->OnGoToActor.AddUObject(this, &AEE_PlayerController::TargetUpdate);
}

void AEE_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(RunSequenceTimer, this, &AEE_PlayerController::RunSequence, 20.f, false);
}

void AEE_PlayerController::TargetUpdate(AEE_DefaultPlaceInteractActor* Actor)
{
	if(LastPlaceInteractActor) LastPlaceInteractActor->SetAIVisible(false);
	Actor->SetAIVisible(true);
	LastPlaceInteractActor = Actor;

	if (GetWorldTimerManager().IsTimerActive(RunSequenceTimer))
	{
		GetWorldTimerManager().ClearTimer(RunSequenceTimer);
	}

	GetWorldTimerManager().SetTimer(RunSequenceTimer, this, &AEE_PlayerController::RunSequence, 20.f, false);
}

void AEE_PlayerController::RunSequence()
{
	AFKPlayer = true;
}