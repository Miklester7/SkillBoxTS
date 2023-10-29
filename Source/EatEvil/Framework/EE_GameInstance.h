// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "EE_Types.h"
#include "EE_GameInstance.generated.h"

UCLASS()
class EATEVIL_API UEE_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	bool GetPlantInfo(FName PlantName, FPlantsInfo& OutInfo);
	bool GetPotionInfo(FName PlantName, FObjectInfo& OutInfo);

	void PutForStorage(const FStorageObject StorageObject);

	void UnlockRecipe(const FPotionRecipes& Recipe);
	const TArray<FPotionRecipes>& GetUnlockedRecipes() { return UnlockedRecipes; }

	const TArray<FName>& GetUnblockedPlants() { return UnblockedPlants; }

	bool GetFromStorage(const FName& ObjectName,const int32 Num);
protected:
	virtual void Init() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DataSettings")
	UDataTable* PlantsInfoTable = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DataSettings")
	UDataTable* PotionsInfoTable = nullptr;

	TArray<FStorageObject> ObjectsInStorage;
	TArray<FName> UnblockedPlants;
	TArray<FPotionRecipes> UnlockedRecipes;
};
