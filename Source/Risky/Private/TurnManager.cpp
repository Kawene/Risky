// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "BaseCharacter.h"

ATurnManager::ATurnManager()
{
	CurrentCharracterIndex = 0;
	PrimaryActorTick.bCanEverTick = true;
	CurrentPhase = EGamePhase::DeploymentPhase;
}

void ATurnManager::Initialize(TArray<ABaseCharacter*>* allPlayers)
{
	Characters = (*allPlayers);

	for (ABaseCharacter* character : Characters)
	{
		character->TurnManagerRef(this);
	}
}

void ATurnManager::StartTurn()
{
	CurrentPhase = EGamePhase::DeploymentPhase;
	Characters[CurrentCharracterIndex]->StartDeploymentPhase();
}

void ATurnManager::ProceedToNextPhase()
{
	switch (CurrentPhase)
	{
	case EGamePhase::DeploymentPhase:
		CurrentPhase = EGamePhase::AttackPhase;
		Characters[CurrentCharracterIndex]->StartAttackPhase();
		break;
	case EGamePhase::AttackPhase:
		CurrentPhase = EGamePhase::FortificationPhase;
		Characters[CurrentCharracterIndex]->StartFortificationPhase();
		break;
	case EGamePhase::FortificationPhase:
		EndTurn();
		break;
	default:
		break;
	}
}

void ATurnManager::EndTurn()
{
	CurrentCharracterIndex = (CurrentCharracterIndex + 1) % Characters.Num();
	StartTurn();
}
