// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EE_PlantActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class EATEVIL_API AEE_PlantActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEE_PlantActor();

	void InitActor(UStaticMesh* Mesh,FVector InitialScale3D);
protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;
protected:
	virtual void BeginPlay() override;


};
