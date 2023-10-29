// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EE_Types.h"
#include "EE_ObjectWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWasSelected, const FPlantsInfo&,const FName&);

class UTextBlock;
class UImage;
class UButton;

UCLASS()
class EATEVIL_API UEE_ObjectWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ObjectName;

	UPROPERTY(meta = (BindWidget))
	UImage* ObjectImage;

	UPROPERTY(meta =(BindWidget))
	UButton* SelectionButton;
public:
	void SetObject(const FPlantsInfo& ObjectInfo,const FName& RowName);

	FOnWasSelected OnWasSelected;
private:
	FPlantsInfo CurrentObject;
	FName RowName;

	UFUNCTION()
	void Selected();
};
