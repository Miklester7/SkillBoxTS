// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/EE_GameInstance.h"

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
		ObjectsInStorage.Add(StorageObject);

		if (!UnblockedPlants.Contains(StorageObject.ObjectRowName))
		{
			UnblockedPlants.Add(StorageObject.ObjectRowName);
		}
	}
}
