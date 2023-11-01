// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EE_AINPC_Character.h"
#include "Components/EE_NPCStateComponent.h"
#include "UI/EE_NPSStatusWidget.h"
#include "Components/WidgetComponent.h"
#include "EEUtils.h"
#include "Animation/EE_AnimNotify_FirstType.h"
#include "Animation/EE_AnimNotify_SecondType.h"
#include "GameFramework/CharacterMovementComponent.h"

AEE_AINPC_Character::AEE_AINPC_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	NPCStateComponent = CreateDefaultSubobject<UEE_NPCStateComponent>(TEXT("NPCStateComponent"));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NPSStatusWidget"));
	WidgetComponent->SetupAttachment(GetRootComponent());
}

void AEE_AINPC_Character::Action()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayAnimMontage(DrinkAnimMontage);
}

void AEE_AINPC_Character::BeginPlay()
{
	Super::BeginPlay();
	
	check(NPSStatusWidgetClass);

	WidgetComponent->SetWidgetClass(NPSStatusWidgetClass);
	auto Widget = Cast<UEE_NPSStatusWidget>(WidgetComponent->GetWidget());
	if (Widget) 
	{
		Widget->SetupComponent(NPCStateComponent);
		Widget->UpdateWidget(0.f, 0.f, 1.f);
	}

	const auto NotifyFT = EEUtils::FindNotifyByClass<UEE_AnimNotify_FirstType>(DrinkAnimMontage);
	if (NotifyFT)
	{
		NotifyFT->OnNotifiedFTypeSignature.AddUObject(this, &ThisClass::PlaySecondAnimMontage);
	}

	const auto NotifyST = EEUtils::FindNotifyByClass<UEE_AnimNotify_SecondType>(ThrowAnimMontage);
	if (NotifyST)
	{
		NotifyST->OnNotifiedSTypeSignature.AddUObject(this, &ThisClass::ActionEnd);
	}

	const auto NotifySTS = EEUtils::FindNotifyByClass<UEE_AnimNotify_SecondType>(SleepAnimMontage);
	if (NotifySTS)
	{
		NotifySTS->OnNotifiedSTypeSignature.AddUObject(this, &ThisClass::ActionEnd);
	}
}

void AEE_AINPC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEE_AINPC_Character::ActionEnd()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AEE_AINPC_Character::PlaySecondAnimMontage()
{
	PlayAnimMontage(ThrowAnimMontage);
}

