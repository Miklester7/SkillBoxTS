// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EE_Types.h"
#include "EE_CreationWidget.generated.h"

class UButton;
class UTextBlock;
class UProgressBar;
class UImage;
class USizeBox;

UCLASS()
class EATEVIL_API UEE_CreationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitWidget(const FName& RowName);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	UButton* FirstTypeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SecondTypeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ThirdTypeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* StartCreateButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FirstTypeName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SecondTypeName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResurceNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ThirdTypeName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SelectedObjectName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ActionStatusName;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* CreateProgressBar;

	UPROPERTY(meta = (BindWidget))
	UImage* ResourceImage;

	UPROPERTY(meta = (BindWidget))
	UImage* SelectedObjectImage;

	UPROPERTY(meta = (BindWidget))
	UImage* FirstTypeImage;

	UPROPERTY(meta = (BindWidget))
	UImage* SecondTypeImage;

	UPROPERTY(meta = (BindWidget))
	UImage* ThirdTypeImage;

	UPROPERTY(meta = (BindWidget))
	USizeBox* ObjectTypesBox;

private:
	FObjectInfo CurrentObjectInfo;

	UFUNCTION()
	void SelectedFirstType();

	UFUNCTION()
	void SelectedSecondType();

	UFUNCTION()
	void SelectedThirdType();

	UFUNCTION()
	void SelectType();

	int8 CurrentIndex{ INDEX_NONE };
	FName ObjectRowName = NAME_None;

	UFUNCTION()
	void CreateObject();

	FTimerHandle CreateTimer;
	float CreateTime{ 15.f };
	float CurrentTime{ 0.f };
	void TimerUpdated();
	void SetToStorage();

	void UpdateResourceSlot();
};