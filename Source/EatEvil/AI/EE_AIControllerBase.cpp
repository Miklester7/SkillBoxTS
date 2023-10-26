// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EE_AIControllerBase.h"
#include "Characters/EE_AICharacterBase.h"

void AEE_AIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<AEE_AICharacterBase>(InPawn);
	if (AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}
