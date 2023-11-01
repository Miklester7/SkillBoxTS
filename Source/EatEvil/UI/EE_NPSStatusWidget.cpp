// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EE_NPSStatusWidget.h"
#include "Components/ProgressBar.h"
#include "Components/EE_NPCStateComponent.h"

void UEE_NPSStatusWidget::SetupComponent(UEE_NPCStateComponent* Component)
{
	Component->OnStatesUpdated.AddUObject(this, &UEE_NPSStatusWidget::UpdateWidget);
}

void UEE_NPSStatusWidget::UpdateWidget(const float Alk, const float AntAlk, const float Nutr)
{
	if (AlkoBar && AntiAlkoBar && NutriBar)
	{
		AlkoBar->SetPercent(Alk);
		AntiAlkoBar->SetPercent(AntAlk);
		NutriBar->SetPercent(Nutr);
	}
}
