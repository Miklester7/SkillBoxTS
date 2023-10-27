// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EE_DraggingComponent.h"

UEE_DraggingComponent::UEE_DraggingComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

void UEE_DraggingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEE_DraggingComponent::TakeObject(const FName& RowName, const FText& ObjectGameName, UTexture2D* Image)
{
	OnTakeObject.Broadcast(RowName, ObjectGameName, Image);
}

void UEE_DraggingComponent::PutObject(const FName& RowName)
{
	OnPutObject.Broadcast(RowName);
}

void UEE_DraggingComponent::CanInteract(EActionType Type, TFunction<void()> Func)
{
	ExecutableFunc = Func;
	OnReadyToInteract.Broadcast(Type);
}

void UEE_DraggingComponent::ExecutableFunction()
{
	if (ExecutableFunc)
	{
		ExecutableFunc();
	}
}
