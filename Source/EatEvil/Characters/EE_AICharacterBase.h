// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EE_Types.h"
#include "EE_AICharacterBase.generated.h"

class UBehaviorTree;
class UEE_DraggingComponent;
class UStaticMeshComponent;

UCLASS()
class EATEVIL_API AEE_AICharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEE_AICharacterBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	bool IsAnimationPlaying() { return bIsAnimationPlaying; }
protected:

	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere,Category = "Components")
	UEE_DraggingComponent* DraggingComponent;

	//SecondType
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* PutAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* PutInStorageAnimMontage;

	//FirstType
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* TakeAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* InstrumentMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BoxMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	FName SocketName;

private:
	void PlayInteractAnim(EActionType Type);

	void Action();
	void PutInStorage();

	void AttachComponents();

	bool bIsAnimationPlaying{ false };
};
