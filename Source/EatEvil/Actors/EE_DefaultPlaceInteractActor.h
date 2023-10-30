// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EE_DefaultPlaceInteractActor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoToActor, AEE_DefaultPlaceInteractActor*);

UCLASS()
class EATEVIL_API AEE_DefaultPlaceInteractActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEE_DefaultPlaceInteractActor();

	FOnGoToActor OnGoToActor;

	void SetAIVisible(bool bIsVisible);

	bool GetAIVisible() { return bIsVisible; }
	FVector GetInteractLocation() { return InteractLocations + GetActorLocation(); }

	virtual void Interact();

	virtual void PlayerInteracted();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Locations", meta = (MakeEditWidget = true))
	FVector InteractLocations;

private:
	bool bIsVisible{ false };
};
