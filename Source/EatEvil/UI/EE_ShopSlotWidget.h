// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EE_ShopSlotWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_SixParams(FOnSelected, UTexture2D*, const FText&, const FName&, UEE_ShopSlotWidget*,const int32,const int8);

class UButton;
class UImage;
class UTextBlock;

UCLASS()
class EATEVIL_API UEE_ShopSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitWidget(UTexture2D* Image,const FText& ObjectName,const FName& RowName,const int32 ObjectNum,const int8 Grade);

	void DisableButton();
	FOnSelected OnSelected;
protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	UImage* ObjectImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ObjectNameBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ObjectsNum;

private:
	UTexture2D* CurrentImage = nullptr;
	FText ObjectName;
	FName ObjectRowName;
	int32 ObjectNum;
	int8 ObjectGrade;

	UFUNCTION()
	void ObjectSelect();
};
