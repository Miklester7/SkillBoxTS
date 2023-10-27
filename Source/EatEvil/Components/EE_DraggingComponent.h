// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EE_Types.h"
#include "EE_DraggingComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTakeObject,const FName&,const FText&,UTexture2D*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPutObject,const FName&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnReadyToInteract,const EActionType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EATEVIL_API UEE_DraggingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEE_DraggingComponent();

	void TakeObject(const FName& RowName,const FText& ObjectGameName, UTexture2D* Image);
	void PutObject(const FName& RowName);

	void CanInteract(EActionType Type, TFunction<void()> Func);
	void ExecutableFunction();
	FOnTakeObject OnTakeObject;
	FOnPutObject OnPutObject;
	FOnReadyToInteract OnReadyToInteract;

protected:
	virtual void BeginPlay() override;

private:
	TFunction<void()> ExecutableFunc;
		
};
