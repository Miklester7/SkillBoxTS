// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EE_LandPurchaseWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPurchased);
DECLARE_MULTICAST_DELEGATE(FOnHide);

class UButton;
class UTextBlock;

UCLASS()
class EATEVIL_API UEE_LandPurchaseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

public:
	void InitWidget(const int32 Cost);

	FOnPurchased OnPurchased;
	FOnHide OnHide;
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* BuyButton;

	UPROPERTY(meta = (BindWidget))
	UButton* HideButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CostText;

private:
	int32 Cost{ 0 };

	UFUNCTION()
	void Buy();
	void CanBuy(const int32 Value);

	UFUNCTION()
	void HideWidget();
};
