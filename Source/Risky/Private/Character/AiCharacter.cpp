// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AiCharacter.h"
#include "Region.h"

AAiCharacter::AAiCharacter()
{
}

void AAiCharacter::StartDeploymentPhase(int32 unitsToDeploy)
{
	RegionsOwned[0]->DeployUnits(1);
	FinishedCurrentPhase();
}

void AAiCharacter::StartAttackPhase()
{
	FinishedCurrentPhase();
}

void AAiCharacter::StartFortificationPhase()
{
	FinishedCurrentPhase();
}
