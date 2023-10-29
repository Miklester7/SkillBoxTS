// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/EE_GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(UEE_GameInstanceLog, All, All);

void UEE_GameInstance::Init()
{
	Super::Init();

	check(PlantsInfoTable);
	UnblockedPlants.Add(FName("Test"));
}

bool UEE_GameInstance::GetPlantInfo(FName PlantName, FPlantsInfo& OutInfo)
{
	const auto Info = PlantsInfoTable->FindRow<FPlantsInfo>(PlantName, "", false);
	if (Info)
	{
		OutInfo = *Info;
		return true;
	}

	return false;
}

bool UEE_GameInstance::GetPotionInfo(FName PlantName, FObjectInfo& OutInfo)
{
	const auto Info = PotionsInfoTable->FindRow<FObjectInfo>(PlantName, "", false);
	if (Info)
	{
		OutInfo = *Info;
		return true;
	}

	return false;
}

void UEE_GameInstance::PutForStorage(const FStorageObject StorageObject)
{
	if (StorageObject.ObjectRowName != NAME_None)
	{
		const auto Index = ObjectsInStorage.IndexOfByPredicate([&](const FStorageObject& Object) {

			return Object.ObjectRowName == StorageObject.ObjectRowName;
			});

		if (Index == INDEX_NONE)
		{
			ObjectsInStorage.Add(StorageObject);
		}
		else
		{
			ObjectsInStorage[Index].Quantity += StorageObject.Quantity;
			UE_LOG(UEE_GameInstanceLog, Warning, TEXT("ObjectsInStorage: Name.%s,Quantity.%i "), *ObjectsInStorage[Index].ObjectRowName.ToString(), ObjectsInStorage[Index].Quantity);
		}
		
		if (!UnblockedPlants.Contains(StorageObject.ObjectRowName))
		{
			UnblockedPlants.Add(StorageObject.ObjectRowName);
		}
	}
}

void UEE_GameInstance::UnlockRecipe(const FPotionRecipes& Recipe)
{
	UnlockedRecipes.Add(Recipe);
}

bool UEE_GameInstance::GetFromStorage(const FName& ObjectName, const int32 Num)
{
	const auto Index = ObjectsInStorage.IndexOfByPredicate([&](const FStorageObject& Object)
		{
			return Object.ObjectRowName == ObjectName;
		});

	if (Index == INDEX_NONE || ObjectsInStorage[Index].Quantity < Num) return false;

	ObjectsInStorage[Index].Quantity -= Num;
	return true;
}