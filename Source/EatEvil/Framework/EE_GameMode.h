// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EE_GameMode.generated.h"

UCLASS(minimalapi)
class AEE_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEE_GameMode();

	bool IsShopEmpty() { return bIsShopEmpty; }
	void SetShopEmpty(bool IsEmpty) { bIsShopEmpty = IsEmpty; }
private:
	bool bIsShopEmpty{ true };
};



