// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "EE_AIStimuliSourceComponent.generated.h"

UCLASS()
class EATEVIL_API UEE_AIStimuliSourceComponent : public UAIPerceptionStimuliSourceComponent
{
	GENERATED_BODY()
	
public:
	UEE_AIStimuliSourceComponent(const FObjectInitializer& ObjectInitializer);
};
