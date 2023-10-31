// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EE_GameWidget.generated.h"

class UTextBlock;

UCLASS()
class EATEVIL_API UEE_GameWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MoneyCounter;

private:
	void UpdateMoneyCounter(const int32 Value);
};
