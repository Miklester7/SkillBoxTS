// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "EE_PlayAnimDecorator.generated.h"


UCLASS()
class EATEVIL_API UEE_PlayAnimDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	//virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
