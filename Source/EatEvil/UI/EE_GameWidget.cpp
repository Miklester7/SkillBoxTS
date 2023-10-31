// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EE_GameWidget.h"
#include "Components/TextBlock.h"
#include "Framework/EE_GameInstance.h"

void UEE_GameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(MoneyCounter);

	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		GI->OnMoneyUpdated.AddUObject(this, &UEE_GameWidget::UpdateMoneyCounter);
		MoneyCounter->SetText(FText::FromString(FString::FromInt(GI->GetMoney())));
	}
}

void UEE_GameWidget::UpdateMoneyCounter(const int32 Value)
{
	MoneyCounter->SetText(FText::FromString(FString::FromInt(Value)));
}
