// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EE_AnimNotify_SecondType.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNotifiedSTypeSignature);

UCLASS()
class EATEVIL_API UEE_AnimNotify_SecondType : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FOnNotifiedSTypeSignature OnNotifiedSTypeSignature;
};
