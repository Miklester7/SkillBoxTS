// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EE_ShopWidget.generated.h"

class UScrollBox;
class UEE_ShopSlotWidget;
class UButton;
class UTextBlock;
class UImage;

UCLASS()
class EATEVIL_API UEE_ShopWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* StorageContainer;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ShopContainer;

	UPROPERTY(meta = (BindWidget))
	UButton* ForSaleButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ObjectNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NumberTriggersName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PowerResult;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NumTriggersResult;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Description;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CostTextResult;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Power;

	UPROPERTY(meta = (BindWidget))
	UImage* ObjectImage;

	UPROPERTY(EditDefaultsOnly,Category = "UI")
	TSubclassOf<UEE_ShopSlotWidget> ShopSlotWidgetClass;
private:
	void OnObjectSelected(UTexture2D* Image, const FText& ObjectName, const FName& RowName, UEE_ShopSlotWidget* Widget,const int32 Num,const int8 Grade);

	UFUNCTION()
	void SendToStore();

	UPROPERTY()
	TObjectPtr<UEE_ShopSlotWidget> SelectedWidget;

	UPROPERTY()
	TObjectPtr<UTexture2D> Image;

	FText ObjName;
	FName ObjRow;
	int32 ObjNum;
	int8 ObjGrade;

	void UpdateStorageWidgets();
	void UpdateShopWidgets();

	void UpdateTextForPotion();
	void UpdateTextForPlant();

	UFUNCTION()
	void CloseWidget();
};
