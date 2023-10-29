// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/EE_GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(UEE_GameInstanceLog, All, All);

void UEE_GameInstance::Init()
{
	Super::Init();

	check(PlantsInfoTable);
	UnblockedPlants.Add(FName("Test"));
}

bool UEE_GameInstance::GetPlantInfo(FName PlantName, FObjectInfo& OutInfo)
{
	const auto Info = PlantsInfoTable->FindRow<FObjectInfo>(PlantName, "", false);
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
