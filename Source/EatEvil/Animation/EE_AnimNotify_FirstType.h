// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EE_AnimNotify_FirstType.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedFTypeSignature, USkeletalMeshComponent*);


UCLASS()
class EATEVIL_API UEE_AnimNotify_FirstType : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FOnNotifiedFTypeSignature OnNotifiedFTypeSignature;
};
