// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/TurnManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Character/BaseCharacter.h"
#include "Risky/RiskyPlayerController.h"
#include "UI/TurnTrackerUI.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Province.h"
#include "Math/UnrealMathUtility.h"
#include "GamePhase.h"

ATurnManager::ATurnManager()
{
	CurrentCharacterIndex = 0;
	CurrentPhase = EGamePhase::DeploymentPhase;
}

void ATurnManager::Initialize(TArray<ABaseCharacter*>* allPlayers)
{
	Characters = (*allPlayers);

	for (ABaseCharacter* character : Characters)
	{
		character->TurnManagerRef(this);
	}

	ARiskyPlayerController* controller = Characters[0]->GetController<ARiskyPlayerController>();
	TurnTrackerUI = CreateWidget<UTurnTrackerUI>(controller, TurnTrackerUIClass);
	TurnTrackerUI->AddToPlayerScreen();

	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProvince::StaticClass(), temp);

	for (AActor* actor : temp)
	{
		AProvince* Province = Cast<AProvince>(actor);
		if (Province)
		{
			Provinces.Add(Province);
		}
	}
}

void ATurnManager::StartTurn()
{
	CurrentPhase = EGamePhase::DeploymentPhase;
	Characters[CurrentCharacterIndex]->
		StartDeploymentPhase();

	FLinearColor LinearColor = FLinearColor(
		Characters[CurrentCharacterIndex]->ColorIdentity.R / 255.0f,
		Characters[CurrentCharacterIndex]->ColorIdentity.G / 255.0f,
		Characters[CurrentCharacterIndex]->ColorIdentity.B / 255.0f
	); 

	TurnTrackerUI->PlayerTracker->SetBrushColor(LinearColor);


}

void ATurnManager::ProceedToNextPhase()
{
	switch (CurrentPhase)
	{
	case EGamePhase::DeploymentPhase:
		CurrentPhase = EGamePhase::AttackPhase;
		TurnTrackerUI->PhaseTracker->SetText(FText::FromString("A"));
		Characters[CurrentCharacterIndex]->StartAttackPhase();
		break;
	case EGamePhase::AttackPhase:
		CurrentPhase = EGamePhase::FortificationPhase;
		TurnTrackerUI->PhaseTracker->SetText(FText::FromString("F"));
		Characters[CurrentCharacterIndex]->StartFortificationPhase();
		break;
	case EGamePhase::FortificationPhase:
		TurnTrackerUI->PhaseTracker->SetText(FText::FromString("D"));
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

	if (index == 0)
	{
		APlayerController* const player = GEngine->GetFirstLocalPlayerController(GetWorld());
		if (AiPhasesSteps == EAiPhasesSteps::NoStop)
		{
			AiPhasesSteps = EAiPhasesSteps::ByTurn;
		}
	}

	Characters.Remove(corpse);
	if (Characters.Num() == 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, "GG well played");
	}
	if (index < CurrentCharacterIndex)
	{
		--CurrentCharacterIndex;
	}
}

void ATurnManager::EndTurn()
{
	CurrentCharacterIndex = (CurrentCharacterIndex + 1) % Characters.Num();
	if (CurrentCharacterIndex == 0 && TotalAiTimes != 0)
	{
		WriteTotalTime();
	}
	StartTurn();
}

int32 ATurnManager::GetsNumberOfUnitsToDeploy(ABaseCharacter* character)
{
	int total = FMath::Max(3, character->RegionsOwned.Num() / 2); // devrait etre 3 round down

	for (AProvince* province : Provinces)
	{
		total += province->GetBonusIfOwner(character);
	}

	return total;
}

TArray<ABaseCharacter*> ATurnManager::GetTurnOrderFrom(ABaseCharacter* character)
{
	TArray<ABaseCharacter*> orderedList;
	int32 startIndex = Characters.Find(character);

	for (int32 i = startIndex; i < Characters.Num(); i++)
	{
		orderedList.Add(Characters[i]);
	}

	for (int32 i = 0; i < startIndex; i++)
	{
		orderedList.Add(Characters[i]);
	}

	return orderedList;
}

void ATurnManager::WriteTotalTime()
{
	FString message;

	message += FString::Printf(TEXT("Total times for the Ai this turn =\t %f\n\n\n\n"), TotalAiTimes);

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
