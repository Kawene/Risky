// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/TurnManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Character/BaseCharacter.h"

ATurnManager::ATurnManager()
{
	CurrentCharracterIndex = 0;
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
	Characters[CurrentCharracterIndex]->
		StartDeploymentPhase(
			GetsNumberOfUnitsToDeploy(
				Characters[CurrentCharracterIndex]
			)
		);
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

void ATurnManager::CharacterDied(ABaseCharacter* corpse)
{
	int32 index = 0;
	for (; index < Characters.Num(); index++)
	{
		if (Characters[index] == corpse)
		{
			break;
		}
	}

	Characters.Remove(corpse);
	if (Characters.Num() == 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, "GG well played");
	}
	if (index < CurrentCharracterIndex)
	{
		--CurrentCharracterIndex;
	}
}

void ATurnManager::EndTurn()
{
	CurrentCharracterIndex = (CurrentCharracterIndex + 1) % Characters.Num();
	if (CurrentCharracterIndex == 0 && TotalAiTimes != 0)
	{
		WriteTotalTime();
	}
	StartTurn();
}

int32 ATurnManager::GetsNumberOfUnitsToDeploy(ABaseCharacter* character)
{
	return character->RegionsOwned.Num() * 3;
}

void ATurnManager::WriteTotalTime()
{
	FString message;

	message += FString::Printf(TEXT("Total times for the aI this turn =\t %f\n\n\n\n"), TotalAiTimes);

	FString filePath = FPaths::ProjectDir() + TEXT("StatsAI.txt");

	FFileHelper::SaveStringToFile(
		message,
		*filePath,
		FFileHelper::EEncodingOptions::AutoDetect,
		&IFileManager::Get(),
		FILEWRITE_Append
	);

	TotalAiTimes = 0;
}
