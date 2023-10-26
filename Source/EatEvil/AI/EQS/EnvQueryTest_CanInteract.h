// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_CanInteract.generated.h"


UCLASS()
class EATEVIL_API UEnvQueryTest_CanInteract : public UEnvQueryTest
{
	GENERATED_BODY()
	
public:
	UEnvQueryTest_CanInteract(const FObjectInitializer& ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
