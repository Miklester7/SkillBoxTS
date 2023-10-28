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
	bool GetPlantInfo(FName PlantName, FObjectInfo& OutInfo);

	void PutForStorage(const FStorageObject StorageObject);
	
	const TArray<FName>& GetUnblockedPlants() { return UnblockedPlants; }
protected:
	virtual void Init() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DataSettings")
	UDataTable* PlantsInfoTable = nullptr;

	TArray<FStorageObject> ObjectsInStorage;
	TArray<FName> UnblockedPlants;
};
