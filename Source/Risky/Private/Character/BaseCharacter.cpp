// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "Manager/TurnManager.h"

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::FinishedCurrentPhase()
{
	TurnManager->ProceedToNextPhase();
}

void ABaseCharacter::StartDeploymentPhase(int32 unitsToDeploy)
{
}

void ABaseCharacter::StartAttackPhase()
{
}

void ABaseCharacter::StartFortificationPhase()
{
}

void ABaseCharacter::TurnManagerRef(ATurnManager* tManager)
{
	TurnManager = tManager;
}

