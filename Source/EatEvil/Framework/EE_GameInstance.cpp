// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/EE_GameInstance.h"

void UEE_GameInstance::Init()
{
	Super::Init();

	check(PlantsInfoTable);
}

bool UEE_GameInstance::GetPlantInfo(FName PlantName, FPlantsInfo& OutInfo)
{
	const auto Info = PlantsInfoTable->FindRow<FPlantsInfo>(PlantName, "", false);
	if (Info)
	{
		OutInfo = *Info;
		return true;
	}

	return false;
}
