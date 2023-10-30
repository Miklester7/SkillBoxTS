// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EE_LandPurchaseWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Framework/EE_GameInstance.h"

void UEE_LandPurchaseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(BuyButton);

	BuyButton->OnClicked.AddDynamic(this, &UEE_LandPurchaseWidget::Buy);
	HideButton->OnClicked.AddDynamic(this, &UEE_LandPurchaseWidget::HideWidget);
}

void UEE_LandPurchaseWidget::InitWidget(const int32 InCost)
{
	CanBuy();

	if(CostText)
	{
		CostText->SetText(FText::FromString(FString::FromInt(InCost)));
		Cost = InCost;
	}
}

void UEE_LandPurchaseWidget::Buy()
{
	auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		GI->SetMoney(-Cost);
		OnPurchased.Broadcast();
	}
}

bool UEE_LandPurchaseWidget::CanBuy()
{
	const auto GI = GetGameInstance<UEE_GameInstance>();
	if (GI)
	{
		if (GI->GetMoney() >= Cost)
		{
			BuyButton->bIsEnabled = false;
		}
	}
	return false;
}

void UEE_LandPurchaseWidget::HideWidget()
{
	OnHide.Broadcast();
}
