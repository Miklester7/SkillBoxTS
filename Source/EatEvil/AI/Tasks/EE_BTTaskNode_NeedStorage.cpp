// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/EE_BTTaskNode_NeedStorage.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EE_AICharacterBase.h"
#include "Components/EE_DraggingComponent.h"

UEE_BTTaskNode_NeedStorage::UEE_BTTaskNode_NeedStorage()
{
	NodeName = "IsNeedStorage";
}

EBTNodeResult::Type UEE_BTTaskNode_NeedStorage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	const auto Actor = BlackBoard->GetValueAsObject(SelfActorKey.SelectedKeyName);
	if (Actor)
	{
		const auto PCharacter = Cast<AEE_AICharacterBase>(Actor);
		if (PCharacter)
		{
			const auto DraggingComponent = PCharacter->GetComponentByClass<UEE_DraggingComponent>();
			if (DraggingComponent->IsEmployed())
			{
				BlackBoard->SetValueAsBool(NeedStorageKey.SelectedKeyName, true);
				return EBTNodeResult::Succeeded;
			}
			BlackBoard->SetValueAsBool(NeedStorageKey.SelectedKeyName, false);
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Succeeded;
}
