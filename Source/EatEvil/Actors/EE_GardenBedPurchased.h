// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/EE_GardenBedActorBase.h"
#include "EE_GardenBedPurchased.generated.h"

class UEE_LandPurchaseWidget;

UCLASS()
class EATEVIL_API AEE_GardenBedPurchased : public AEE_GardenBedActorBase
{
	GENERATED_BODY()
	
public:
	AEE_GardenBedPurchased();

protected:
	UPROPERTY(EditAnywhere,Category = "Buy")
	int32 Cost{ 2000 };

	bool Purchased{ false };

	UPROPERTY(EditDefaultsOnly, Category = "Buy")
	TSubclassOf<UEE_LandPurchaseWidget> LandPurchaseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* GarbageMeshComponent;
protected:
	virtual void BeginPlay() override;

	virtual void InitWidget() override;

	virtual void InteractZoneOverlaped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	//virtual void OnMouseReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased) override;

	void UnlockPlace();

	void HideWidget();
};
