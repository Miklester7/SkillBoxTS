// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EE_NPSStatusWidget.generated.h"

class UProgressBar;
class UEE_NPCStateComponent;

UCLASS()
class EATEVIL_API UEE_NPSStatusWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetupComponent(UEE_NPCStateComponent* Component);

	void UpdateWidget(const float Alk, const float AntAlk, const float Nutr);
protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* AlkoBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* AntiAlkoBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* NutriBar;
};

