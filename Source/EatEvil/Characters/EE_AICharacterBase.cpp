// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EE_AICharacterBase.h"
#include "Components/EE_DraggingComponent.h"

AEE_AICharacterBase::AEE_AICharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	DraggingComponent = CreateDefaultSubobject<UEE_DraggingComponent>(TEXT("DraggingComponent"));
}

void AEE_AICharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}