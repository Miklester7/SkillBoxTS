// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EE_GardenBedActorBase.h"

// Sets default values
AEE_GardenBedActorBase::AEE_GardenBedActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEE_GardenBedActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEE_GardenBedActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

