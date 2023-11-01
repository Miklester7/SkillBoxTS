// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EE_Bottle.generated.h"

class UStaticMeshComponent;

UCLASS()
class EATEVIL_API AEE_Bottle : public AActor
{
	GENERATED_BODY()
	
public:	
	AEE_Bottle();

	void SetMesh(UStaticMesh* Mesh);
	void EnablePhisics(const FVector& Impuls);

protected:
	UPROPERTY(EditDefaultsOnly,Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USceneComponent* SceneComponent;

protected:
	virtual void BeginPlay() override;

};
