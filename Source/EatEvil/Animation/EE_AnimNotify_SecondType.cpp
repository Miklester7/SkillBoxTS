// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EE_AnimNotify_SecondType.h"

void UEE_AnimNotify_SecondType::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifiedSTypeSignature.Broadcast();

	Super::Notify(MeshComp, Animation);
}
