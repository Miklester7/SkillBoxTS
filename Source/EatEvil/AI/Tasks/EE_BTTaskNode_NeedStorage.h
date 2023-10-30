// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EE_BTTaskNode_NeedStorage.generated.h"


UCLASS()
class EATEVIL_API UEE_BTTaskNode_NeedStorage : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UEE_BTTaskNode_NeedStorage();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector NeedStorageKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector SelfActorKey;
};
