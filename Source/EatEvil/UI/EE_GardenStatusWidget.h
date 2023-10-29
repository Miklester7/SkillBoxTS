// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EE_Types.h"
#include "EE_GardenStatusWidget.generated.h"

class UImage;
class AEE_GardenBedActorBase;
class UTextBlock;
class UButton;
class UScrollBox;
class UEE_ObjectWidget;
class AEE_GardenBedActorBase;

DECLARE_MULTICAST_DELEGATE(FOnWidgetHide);
DECLARE_MULTICAST_DELEGATE(FGetContent);

UCLASS()
class EATEVIL_API UEE_GardenStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateTimer(float Percent);

	void UpdateStatus(EGardenState State);

	void InitWidget(AEE_GardenBedActorBase* OwnerActor);

	void SetOwningActors(AEE_GardenBedActorBase* Actor) { GardenBedActor = Actor; }

	FOnWidgetHide OnWidgetHide;
	FGetContent GetContentDelegate;
protected:
	virtual void NativeOnInitialized() override;
	
protected:
	UPROPERTY(EditDefaultsOnly,Category = "Textures")
	UMaterialInstance* BarMaterial;

	UPROPERTY(meta = (BindWidget))
	UImage* PlantImage;

	UPROPERTY(meta = (BindWidget))
	UImage* CircleBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlantNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatusText;

	UPROPERTY(meta = (BindWidget))
	UButton* ActionButton;

	UPROPERTY(meta = (BindWidget))
	UButton* HideWidgetButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowScrollBox;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ObjectsBox;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Content")
	TSubclassOf<UEE_ObjectWidget> ObjectWidgetClass;
private:
	UFUNCTION()
	void OnActionButtonClicked();

	UFUNCTION()
	void HideWidget();
private:
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> BarMaterialDynamic;

	EGardenState CurrentState;

	UPROPERTY()
	TArray<TObjectPtr<UEE_ObjectWidget>> ObjectWidgets;

	void ClearObjectWidgets();

	UPROPERTY()
	TObjectPtr<AEE_GardenBedActorBase> GardenBedActor;

	void PlantWasSelected(const FPlantsInfo& PlantInfo, const FName& RowName);
};
