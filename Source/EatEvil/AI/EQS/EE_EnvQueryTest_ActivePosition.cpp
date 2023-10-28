// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EE_EnvQueryTest_ActivePosition.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Actors/EE_DefaultPlaceInteractActor.h"

UEE_EnvQueryTest_ActivePosition::UEE_EnvQueryTest_ActivePosition(const FObjectInitializer& ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEE_EnvQueryTest_ActivePosition::RunTest(FEnvQueryInstance& QueryInstance) const
{
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		const auto GBActor = Cast<AEE_DefaultPlaceInteractActor>(ItemActor);
		if (!GBActor) continue;

		if (GBActor->GetAIVisible())
		{
			It.SetScore(TestPurpose, FilterType, true, true);
		}
		else
		{
			It.ForceItemState(EEnvItemStatus::Failed);
		}
	}
}
