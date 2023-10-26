// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EnvQueryTest_CanInteract.h"
#include "Actors/EE_GardenBedActorBase.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "EE_Types.h"

UEnvQueryTest_CanInteract::UEnvQueryTest_CanInteract(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_CanInteract::RunTest(FEnvQueryInstance& QueryInstance) const
{
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		const auto GBActor = Cast<AEE_GardenBedActorBase>(ItemActor);
		if (!GBActor) continue;

		if (GBActor->CanInteract())
		{
			It.SetScore(TestPurpose, FilterType, true,true);
		}
		else
		{
			It.ForceItemState(EEnvItemStatus::Failed);
		}
	}
}
