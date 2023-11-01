// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/EE_ShopService.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EE_GameMode.h"

UEE_ShopService::UEE_ShopService()
{
	NodeName = "CanShopping";
}

void UEE_ShopService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();

	auto GameMode = Cast<AEE_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		if (GameMode->IsShopEmpty())
		{
			GameMode->SetShopEmpty(false);
			BlackBoard->SetValueAsBool(CanGoKey.SelectedKeyName, true);
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

