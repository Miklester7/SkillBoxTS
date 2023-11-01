// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/EE_GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(UEE_GameInstanceLog, All, All);

void UEE_GameInstance::Init()
{
	Super::Init();

	check(PlantsInfoTable);
	UnblockedPlants.Add(FName("Turnip"));
	UnblockedPlants.Add(FName("Onion"));
	UnblockedPlants.Add(FName("Radish"));
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

			return Object.ObjectRowName == StorageObject.ObjectRowName && Object.Grade == StorageObject.Grade;
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

		OnStorageUpdated.Broadcast();
	}
}

void UEE_GameInstance::PutForShop(const FStorageObject StorageObject)
{
	if (StorageObject.ObjectRowName != NAME_None)
	{
		const auto Index = ObjectsInShop.IndexOfByPredicate([&](const FStorageObject& Object) {

			return Object.ObjectRowName == StorageObject.ObjectRowName && Object.Grade == StorageObject.Grade;
			});

		if (Index == INDEX_NONE)
		{
			ObjectsInShop.Add(StorageObject);
		}
		else
		{
			ObjectsInShop[Index].Quantity += StorageObject.Quantity;
			UE_LOG(UEE_GameInstanceLog, Warning, TEXT("ObjectsInShop: Name.%s,Quantity.%i "), *ObjectsInShop[Index].ObjectRowName.ToString(), ObjectsInShop[Index].Quantity);
		}

		if (!UnblockedPlants.Contains(StorageObject.ObjectRowName))
		{
			UnblockedPlants.Add(StorageObject.ObjectRowName);
		}
		OnShopUpdated.Broadcast();
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
	OnStorageUpdated.Broadcast();

	return true;
}

bool UEE_GameInstance::GetFromShop(const FName& ObjectName, const int32 Grade)
{
	const auto Index = ObjectsInShop.IndexOfByPredicate([&](const FStorageObject& Object)
		{
			return Object.ObjectRowName == ObjectName && Object.Grade == Grade;
		});

	if (Index == INDEX_NONE) return false;

	ObjectsInShop[Index].Quantity -= 1;
	if (ObjectsInShop[Index].Quantity == 0)
	{
		ObjectsInShop.RemoveAt(Index);
	}

	OnShopUpdated.Broadcast();

	return true;
}

void UEE_GameInstance::SetMoney(const int32 Value)
{
	Money = FMath::Clamp(Money + Value, 0, INT32_MAX);
	OnMoneyUpdated.Broadcast(Money);
}

void UEE_GameInstance::SendToShop(const FName& RowName, const int32 Grade)
{
	int8 Index;

	if(Grade >= 0)
	{
		Index = ObjectsInStorage.IndexOfByPredicate([&](const FStorageObject& Object)
			{
				return Object.ObjectRowName == RowName && Object.Grade == Grade;
			});
	}
	else
	{
		Index = ObjectsInStorage.IndexOfByPredicate([&](const FStorageObject& Object)
			{
				return Object.ObjectRowName == RowName;
			});
	}

	if (Index != INDEX_NONE)
	{
		PutForShop(ObjectsInStorage[Index]);
		ObjectsInStorage[Index].Quantity = 0;
	}

}