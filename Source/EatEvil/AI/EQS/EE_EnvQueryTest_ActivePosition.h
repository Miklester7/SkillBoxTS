// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EE_EnvQueryTest_ActivePosition.generated.h"

UCLASS()
class EATEVIL_API UEE_EnvQueryTest_ActivePosition : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UEE_EnvQueryTest_ActivePosition(const FObjectInitializer& ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
