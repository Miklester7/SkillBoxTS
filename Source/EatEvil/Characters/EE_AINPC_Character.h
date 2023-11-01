// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EE_AINPC_Character.generated.h"

class UBehaviorTree;
class UEE_NPCStateComponent;
class UWidgetComponent;
class UEE_NPSStatusWidget;
class UAnimMontage;
class AEE_Bottle;
class USkeletalMeshComponent;

UCLASS()
class EATEVIL_API AEE_AINPC_Character : public ACharacter
{
	GENERATED_BODY()

public:
	AEE_AINPC_Character();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	void Action();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,Category = "Components")
	UEE_NPCStateComponent* NPCStateComponent;

	UPROPERTY(EditDefaultsOnly,Category = "Components")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditDefaultsOnly,Category = "Components")
	TSubclassOf<UEE_NPSStatusWidget>  NPSStatusWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DrinkAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* ThrowAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* SleepAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* UpAnimMontage;

	UPROPERTY(EditDefaultsOnly,Category = "SpawnActor")
	TSubclassOf<AEE_Bottle> BottleActorClass;

	UPROPERTY(EditAnywhere,Category = "SpawnActor")
	FName SocketName;
public:	 
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool GetDrunk() { return Drunk; }
private:
	void ActionEnd(USkeletalMeshComponent* Mesh);
	void PlaySecondAnimMontage(USkeletalMeshComponent* Mesh);

	UPROPERTY()
	TObjectPtr<AEE_Bottle> CurrentBottleActor;

	void SetDrunk(bool Value);
	bool Drunk{ false };

	void ReturnMovement(USkeletalMeshComponent* SkeletalMesh);

	void PlayUpMontage(USkeletalMeshComponent* SkeletalMesh);
};
