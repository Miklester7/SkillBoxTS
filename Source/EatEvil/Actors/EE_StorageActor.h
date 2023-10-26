// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EE_StorageActor.generated.h"

class UBoxComponent;

UCLASS()
class EATEVIL_API AEE_StorageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEE_StorageActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* InteractZoneCollision;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Locations", meta = (MakeEditWidget = true))
	FVector InteractLocations;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};