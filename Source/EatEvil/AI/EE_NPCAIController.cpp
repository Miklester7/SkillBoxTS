// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EE_NPCAIController.h"
#include "Characters/EE_AINPC_Character.h"

void AEE_NPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<AEE_AINPC_Character>(InPawn);
	if (AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}
