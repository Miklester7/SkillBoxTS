// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EE_AIControllerBase.generated.h"


UCLASS()
class EATEVIL_API AEE_AIControllerBase : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
