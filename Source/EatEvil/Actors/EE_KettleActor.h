// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/EE_DefaultPlaceInteractActor.h"
#include "EE_KettleActor.generated.h"

class UWidgetComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UEE_KettleMenuWidget;

UCLASS()
class EATEVIL_API AEE_KettleActor : public AEE_DefaultPlaceInteractActor
{
	GENERATED_BODY()
	
public:
	AEE_KettleActor();

	virtual void Interact() override;
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UWidgetComponent* InteractWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly,Category = "UI")
	TSubclassOf<UEE_KettleMenuWidget> KettleMenuWidgetClass;

private:
	void HideWidget();

	UFUNCTION()
	void OnCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnEndCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnMouseReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);

};
