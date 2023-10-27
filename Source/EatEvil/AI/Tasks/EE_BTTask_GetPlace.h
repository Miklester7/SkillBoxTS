// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EE_BTTask_GetPlace.generated.h"


UCLASS()
class EATEVIL_API UEE_BTTask_GetPlace : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UEE_BTTask_GetPlace();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PlaceLocKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector InteractActorKey;
};
