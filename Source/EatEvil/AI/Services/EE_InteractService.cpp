// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/EE_InteractService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EE_PlayerController.h"

UEE_InteractService::UEE_InteractService()
{
	NodeName = "CheckAFK";
}

void UEE_InteractService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	const auto PController = GetWorld()->GetFirstPlayerController<AEE_PlayerController>();
	if (PController)
	{
		if (PController->GetAFKPlayer())
		{
			BlackBoard->SetValueAsBool(RunSequenceActorKey.SelectedKeyName, true);
		}
		else
		{
			BlackBoard->SetValueAsBool(RunSequenceActorKey.SelectedKeyName, false);
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
