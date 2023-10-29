// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/EE_IsBusy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EE_IsBusy.h"
#include "Characters/EE_AICharacterBase.h"

UEE_IsBusy::UEE_IsBusy()
{
	NodeName = "IsBusy";
}

bool UEE_IsBusy::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	const auto AICharacter = Cast<AEE_AICharacterBase>(BlackBoard->GetValueAsObject(SelfActorKey.SelectedKeyName));
	if (AICharacter && AICharacter->IsAnimationPlaying()) return false;

	return true;
}
