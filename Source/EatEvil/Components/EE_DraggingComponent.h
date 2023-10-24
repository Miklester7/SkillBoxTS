// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EE_DraggingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EATEVIL_API UEE_DraggingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEE_DraggingComponent();

protected:
	virtual void BeginPlay() override;
		
};
