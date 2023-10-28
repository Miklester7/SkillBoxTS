// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_DefaultPlaceInteractActor.h"
#include "EE_PlayerController.h"

AEE_DefaultPlaceInteractActor::AEE_DefaultPlaceInteractActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEE_DefaultPlaceInteractActor::SetAIVisible(bool InbIsVisible)
{
	bIsVisible = InbIsVisible;
}

void AEE_DefaultPlaceInteractActor::Interact()
{
	OnGoToActor.Broadcast(this);
}

void AEE_DefaultPlaceInteractActor::BeginPlay()
{
	Super::BeginPlay();

	auto PlController = GetWorld()->GetFirstPlayerController<AEE_PlayerController>();
	if (PlController)
	{
		PlController->AddPlaceInteractActor(this);
	}
}
