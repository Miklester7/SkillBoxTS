// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EE_Types.h"
#include "EE_GardenBedActorBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerUpdated, float);

class UWidgetComponent;
class AEE_PlantActor;
class UEE_GardenStatusWidget;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class EATEVIL_API AEE_GardenBedActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEE_GardenBedActorBase();

	FOnTimerUpdated OnTimerUpdated;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnEndCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnMouseReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);

	void SetPlant();

	void GrowthCheck();

	void HideWidget();
protected:
	UPROPERTY(EditAnywhere,Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UWidgetComponent* InteractWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UEE_GardenStatusWidget> GardenStatusWidgetClass;

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

	FTimerHandle GrowthRateTimer;
	float CurrentTime{ 0.f };
};
