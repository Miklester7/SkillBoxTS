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

void UEE_DraggingComponent::TakeObject(const FStorageObject StorageObject, const FText& ObjectGameName, UTexture2D* Image)
{
	CurrentObject = StorageObject;
	OnTakeObject.Broadcast(StorageObject.ObjectRowName, ObjectGameName, Image);
}

bool UEE_DraggingComponent::PutObject(FStorageObject& StorageObject)
{
	if (CurrentObject.ObjectRowName != NAME_None)
	{
		OnPutObject.Broadcast(StorageObject.ObjectRowName);
		StorageObject = CurrentObject;

		return true;
	}
	return false;
}

void UEE_DraggingComponent::ClearObject()
{
	CurrentObject.ObjectRowName = NAME_None;
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
