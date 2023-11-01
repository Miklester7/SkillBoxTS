// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "EE_Types.h"
#include "EE_GameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnStorageUpdated);
DECLARE_MULTICAST_DELEGATE(FOnShopUpdated);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoneyUpdated,const int32);
UCLASS()
class EATEVIL_API UEE_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	bool GetPlantInfo(FName PlantName, FPlantsInfo& OutInfo);
	bool GetPotionInfo(FName PlantName, FObjectInfo& OutInfo);

	void PutForStorage(const FStorageObject StorageObject);
	void PutForShop(const FStorageObject StorageObject);

	void UnlockRecipe(const FPotionRecipes& Recipe);
	const TArray<FPotionRecipes>& GetUnlockedRecipes() { return UnlockedRecipes; }

	const TArray<FName>& GetUnblockedPlants() { return UnblockedPlants; }

	bool GetFromStorage(const FName& ObjectName,const int32 Num);
	bool GetFromShop(const FName& ObjectName, const int32 Grade);
	const TArray<FStorageObject>& GetAllObjectsFromStorage() { return ObjectsInStorage; }
	const TArray<FStorageObject>& GetAllObjectsFromShop() { return ObjectsInShop; }

	void SetMoney(const int32 Value);
	const int32 GetMoney() { return Money; }

	void SendToShop(const FName& RowName, const int32 Grade = -1);

	FOnStorageUpdated OnStorageUpdated;
	FOnShopUpdated OnShopUpdated;
	FOnMoneyUpdated OnMoneyUpdated;

	float GetPriceMultiplier() { return PriceMultiplier; }
protected:
	virtual void Init() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DataSettings")
	UDataTable* PlantsInfoTable = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DataSettings")
	UDataTable* PotionsInfoTable = nullptr;

	TArray<FStorageObject> ObjectsInStorage;
	TArray<FStorageObject> ObjectsInShop;

	TArray<FName> UnblockedPlants;

	UPROPERTY(EditDefaultsOnly,Category = "Game")
	TArray<FPotionRecipes> UnlockedRecipes;

	int32 Money{ 2000 };

	float PriceMultiplier{ 0.f };
};
