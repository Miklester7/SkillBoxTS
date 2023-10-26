// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/EE_InteractService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/EE_GardenBedActorBase.h"

UEE_InteractService::UEE_InteractService()
{
	NodeName = "GetPlace";
}

void UEE_InteractService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	const auto Actor = BlackBoard->GetValueAsObject(InteractActorKey.SelectedKeyName);
	if (Actor)
	{
		const auto GardenActor = Cast<AEE_GardenBedActorBase>(Actor);
		if (GardenActor)
		{
			BlackBoard->SetValueAsVector(PlaceLocKey.SelectedKeyName, GardenActor->GetInteractLocation());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
