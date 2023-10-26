// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EE_AICharacterBase.generated.h"

class UBehaviorTree;
class UEE_DraggingComponent;

UCLASS()
class EATEVIL_API AEE_AICharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEE_AICharacterBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
protected:

	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere,Category = "Components")
	UEE_DraggingComponent* DraggingComponent;
};
