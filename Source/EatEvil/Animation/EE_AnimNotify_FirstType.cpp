// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EE_AnimNotify_FirstType.h"

void UEE_AnimNotify_FirstType::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifiedFTypeSignature.Broadcast(MeshComp);

	Super::Notify(MeshComp, Animation);
}
