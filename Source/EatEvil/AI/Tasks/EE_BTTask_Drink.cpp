// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/EE_BTTask_Drink.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EE_AINPC_Character.h"
#include "Kismet/GameplayStatics.h"
#include "EE_GameMode.h"

UEE_BTTask_Drink::UEE_BTTask_Drink()
{
	NodeName = "Drink";
}

EBTNodeResult::Type UEE_BTTask_Drink::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	const auto SelfActor = BlackBoard->GetValueAsObject(SelfActorKey.SelectedKeyName);
	const auto Character = Cast<AEE_AINPC_Character>(SelfActor);
	if (Character)
	{
		Character->Action();
		BlackBoard->SetValueAsBool(CanGoKey.SelectedKeyName, false);
		auto GameMode = Cast<AEE_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->SetShopEmpty(true);
		}
	}

	return EBTNodeResult::Type();
}
