// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/EE_BTTask_GetPlace.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/EE_DefaultPlaceInteractActor.h"

UEE_BTTask_GetPlace::UEE_BTTask_GetPlace()
{
	NodeName = "GetInteractLocation";
}

EBTNodeResult::Type UEE_BTTask_GetPlace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	const auto Actor = BlackBoard->GetValueAsObject(InteractActorKey.SelectedKeyName);
	if (Actor)
	{
		const auto InteractActor = Cast<AEE_DefaultPlaceInteractActor>(Actor);
		if (InteractActor)
		{
			BlackBoard->SetValueAsVector(PlaceLocKey.SelectedKeyName, InteractActor->GetInteractLocation());
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
