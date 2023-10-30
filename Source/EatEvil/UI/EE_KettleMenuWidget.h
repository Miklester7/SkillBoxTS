// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EE_KettleMenuWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCloseButton);

class UEE_CreationWidget;
class UVerticalBox;
class UButton;

UCLASS()
class EATEVIL_API UEE_KettleMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnCloseButton OnCloseButton;

	void UpdateWidgets();

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(EditDefaultsOnly,Category = "Craft")
	TArray<FName> CraftObjectNames;

	UPROPERTY(EditDefaultsOnly, Category = "Craft")
	TSubclassOf<UEE_CreationWidget> CreationWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* CreatWidgetsContainer;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;
private:
	UFUNCTION()
	void OnCloseButtonClicked();
};
