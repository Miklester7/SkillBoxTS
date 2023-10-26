// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EE_InteractService.generated.h"

UCLASS()
class EATEVIL_API UEE_InteractService : public UBTService
{
	GENERATED_BODY()
	
public:
	UEE_InteractService();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AI")
	FBlackboardKeySelector PlaceLocKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector InteractActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
