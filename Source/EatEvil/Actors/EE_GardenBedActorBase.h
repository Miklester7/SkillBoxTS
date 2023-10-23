// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EE_Types.h"
#include "EE_GardenBedActorBase.generated.h"

class UWidgetComponent;
class AEE_PlantActor;

UCLASS()
class EATEVIL_API AEE_GardenBedActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEE_GardenBedActorBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Test(AActor* TouchedActor);

	void SetPlant();
protected:
	UPROPERTY(EditAnywhere,Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UWidgetComponent* InteractWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Content")
	FName PlantRow = NAME_None;

	UPROPERTY(EditDefaultsOnly,Category = "Content")
	TSubclassOf<AEE_PlantActor> PlantActorClass;
private:
	UPROPERTY(EditAnywhere,Category = "Locations", meta = (MakeEditWidget = true))
	TArray<FVector> SpawnMeshLocations;

	UPROPERTY()
	TArray<TObjectPtr<AEE_PlantActor>> Plants;

	FPlantsInfo CurrentPlantInfo;

	bool bIsClear{ true };
};
