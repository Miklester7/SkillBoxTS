// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EE_HUD.generated.h"

class UEE_GameWidget;

UCLASS()
class EATEVIL_API AEE_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly,Category = "UI")
	TSubclassOf<UEE_GameWidget> GameWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UEE_GameWidget> GameWidget;
};
