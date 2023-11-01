// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EE_NPCStateComponent.h"

UEE_NPCStateComponent::UEE_NPCStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

const FName& UEE_NPCStateComponent::GetNeededDrink()
{
	if (Nutrients > 0.5f)
	{
		if (Alcohol < 1.f)
		{
			return AlcoholRowName;
		}
		else if (AntiAlcohol < 0.7f && Alcohol > 0.2f)
		{
			return AntiAlcoholRowName;
		}

		return NutrientsRowName;
	}
	else
	{
		return NutrientsRowName;
	}
	
}

const FName& UEE_NPCStateComponent::CanTakeAlcohol()
{
	return AlcoholRowName;
}

void UEE_NPCStateComponent::ObjectNotFound()
{
	OnObjectNotFoud.Broadcast();
}

void UEE_NPCStateComponent::Drink(const FName& DrinkName, const float Effect, UStaticMesh* Mesh)
{
	OnDrink.Broadcast();
	CurrentMesh = Mesh;

	if (DrinkName == AlcoholRowName)
	{
		const float NewValue = Alcohol + Effect;
		if (NewValue > 1)
		{
			Alcohol = 1.f;
			Nutrients = FMath::Clamp(Nutrients - (NewValue - 1.f), 0.f, 1.f);
			Drunk = true;
			OnDrunk.Broadcast(Drunk);
		}
		else
		{
			Alcohol = NewValue;
		}
		return;
	}

	if (DrinkName == AntiAlcoholRowName)
	{
		AntiAlcohol = FMath::Clamp(AntiAlcohol + Effect, 0.f, 1.f);
		Alcohol = FMath::Clamp(Alcohol - Effect, 0.f, 1.f);
		return;
	}

	if (DrinkName == NutrientsRowName)
	{
		Nutrients = FMath::Clamp(Nutrients + Effect, 0.f, 1.f);
	}
}

void UEE_NPCStateComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(UpdateTimer, this, &UEE_NPCStateComponent::Update,0.25f,true);
	
}

void UEE_NPCStateComponent::Update()
{
	AntiAlcohol = FMath::Clamp(AntiAlcohol - 0.005f, 0.f, 1.f);
	Nutrients = FMath::Clamp(Nutrients - 0.0020f, 0.f, 1.f);

	OnStatesUpdated.Broadcast(Alcohol / 1.f, AntiAlcohol / 1.f, Nutrients / 1.f);

	if (Drunk && Alcohol < 0.5f)
	{
		Drunk = false;
		OnDrunk.Broadcast(Drunk);
	}
}
