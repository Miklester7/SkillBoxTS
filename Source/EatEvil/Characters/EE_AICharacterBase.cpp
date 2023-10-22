// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EE_AICharacterBase.h"

// Sets default values
AEE_AICharacterBase::AEE_AICharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEE_AICharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEE_AICharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEE_AICharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

