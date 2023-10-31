// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EE_HUD.h"
#include "UI/EE_GameWidget.h"

void AEE_HUD::BeginPlay()
{
	check(GameWidgetClass);

	Super::BeginPlay();

	GameWidget = CreateWidget<UEE_GameWidget>(GetWorld(), GameWidgetClass);
	if (GameWidget)
	{
		GameWidget->AddToViewport();
	}
}
