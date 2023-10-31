// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/EE_DefaultPlaceInteractActor.h"
#include "EE_ShopActor.generated.h"

class UEE_ShopWidget;
class UBoxComponent;
class UStaticMeshComponent;
class UEE_ShopWidget;

UCLASS()
class EATEVIL_API AEE_ShopActor : public AEE_DefaultPlaceInteractActor
{
	GENERATED_BODY()
	
public:
	AEE_ShopActor();
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly,Category = "UI")
	TSubclassOf<UEE_ShopWidget> ShopWidgetClass;
private:
	UFUNCTION()
	void OnCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnEndCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnMouseReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);
};
