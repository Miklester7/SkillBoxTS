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
private:
	UFUNCTION()
	void OnActionButtonClicked();

	UFUNCTION()
	void HideWidget();
private:
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> BarMaterialDynamic;

	EGardenState CurrentState;
};
