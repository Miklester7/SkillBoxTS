// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EE_Types.h"
#include "EE_StorageActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

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
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Locations", meta = (MakeEditWidget = true))
	FVector InteractLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnEngCursorOver(UPrimitiveComponent* TouchedComponent);

	void PutForStorage();

	FStorageObject CurrentObject;
};