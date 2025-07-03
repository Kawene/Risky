// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/TurnManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Character/BaseCharacter.h"
#include "Risky/RiskyPlayerController.h"
#include "UI/TurnTrackerUI.h"
#include "Ui/PlayerInformationUI.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Province.h"
#include "Math/UnrealMathUtility.h"
#include "GamePhase.h"
#include "Character/PlayerCharacter.h"
#include "Character/AiCharacter.h"
#include "SettingsSaved.h"

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

	FString saveSlotName = TEXT("SettingsSaveSlot");
	int32 userIndex = 0;
	USettingsSaved* settings = Cast<USettingsSaved>(UGameplayStatics::LoadGameFromSlot(saveSlotName, userIndex));
	AiPhasesSteps = settings->GetPhasesSteps();

	StartTurn();
}

void ATurnManager::StartTurn()
{
	CurrentPhase = EGamePhase::DeploymentPhase;
	Characters[CurrentCharacterIndex]->StartDeploymentPhase();

	FPlayerInformationData playerInformation = FPlayerInformationData(this, Characters[CurrentCharacterIndex]);
	TurnTrackerUI->PlayerInformation->InitializeData(Characters[CurrentCharacterIndex]->ColorIdentity, &playerInformation);
	if (CurrentCharacterIndex > 0)
		TurnTrackerUI->DeploymentInformation(0);
	else
		TurnTrackerUI->DeploymentInformation(GetsNumberOfUnitsToDeploy(Characters[CurrentCharacterIndex]));
}

void ATurnManager::ProceedToNextPhase()
{
	switch (CurrentPhase)
	{
	case EGamePhase::DeploymentPhase:
		CurrentPhase = EGamePhase::AttackPhase;
		TurnTrackerUI->AttackInformation();

		Characters[CurrentCharacterIndex]->StartAttackPhase();
		break;
	case EGamePhase::AttackPhase:
		CurrentPhase = EGamePhase::FortificationPhase;
		TurnTrackerUI->FortificationInformation();

		Characters[CurrentCharacterIndex]->StartFortificationPhase();
		break;
	case EGamePhase::FortificationPhase:
		EndTurn();
		break;
	default:
		break;
	}
	UpdateTurnTrackerUI(Characters[CurrentCharacterIndex]);
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
		if (AiPhasesSteps == EAiPhasesSteps::NoStop)
		{
			AiPhasesSteps = EAiPhasesSteps::ByTurn;
		}
		PlayerDead = true;
		if (CurrentCharacterIndex == 0)
		{
			EndTurn();
		}

		StaticCast<APlayerCharacter*>(Characters[0])->ShowDefeatScreen();
		return;
	}

	if (GetCurrentPlayersAliveCount() == 1)
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
			{
					if (APlayerCharacter* Player = Cast<APlayerCharacter>(Characters[0]))
					{
						Player->ShowVictoryScreen();
					}
			});
	}
}

void ATurnManager::EndTurn()
{
	do {
		CurrentCharacterIndex = (CurrentCharacterIndex + 1) % Characters.Num();
	} while (Characters[CurrentCharacterIndex]->CharacterDead);

	if (CurrentCharacterIndex == 0 && TotalAiTimes != 0)
	{
		if (!PlayerDead)
		{
			APlayerCharacter* player = StaticCast<APlayerCharacter*>(Characters[0]);
			player->TransferTo(true);
		}
		else {
			CurrentCharacterIndex++;
		}

		WriteTotalTime();
	}
	else if (CurrentCharacterIndex == 1 && !PlayerDead) {
		APlayerCharacter* player = StaticCast<APlayerCharacter*>(Characters[0]);
		player->TransferTo(false);
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

	for (int32 i = startIndex + 1; i < Characters.Num(); i++)
	{
		orderedList.Add(Characters[i]);
	}

	if (!PlayerDead)
	{
		APlayerCharacter* player = StaticCast<APlayerCharacter*>(Characters[0]);
		orderedList.Add(StaticCast<ABaseCharacter*>(player->AiPlayer));
	}

	for (int32 i = 1; i < startIndex; i++)
	{
		orderedList.Add(Characters[i]);
	}

	return orderedList;
}

void ATurnManager::UpdateTurnTrackerUI(ABaseCharacter* character, int32 remainingUnits)
{
	FPlayerInformationData playerInformation = FPlayerInformationData(this, character);
	TurnTrackerUI->PlayerInformation->UpdateInformation(&playerInformation);

	if (CurrentPhase == EGamePhase::DeploymentPhase && remainingUnits > 0)
	{
		TurnTrackerUI->DeploymentInformation(remainingUnits);
	}
}

void ATurnManager::WriteTotalTime()
{
	FString message;
	FString filePath = FPaths::ProjectDir() + TEXT("StatsAI.txt");

	if (TotalAiTimes > 100)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Ai turn took more then 0.1 second!!");
		message += FString::Printf(TEXT("Total time for the Ai this turn =\t %f Busted the time limit!!\n\n\n\n"), TotalAiTimes);

	}
	else {
		message += FString::Printf(TEXT("Total time for all Ai this turn =\t %f\n\n\n\n"), TotalAiTimes);
	}

	FFileHelper::SaveStringToFile(
		message,
		*filePath,
		FFileHelper::EEncodingOptions::AutoDetect,
		&IFileManager::Get(),
		FILEWRITE_Append
	);
	TotalAiTimes = 0;
}

int32 ATurnManager::GetCurrentPlayersAliveCount()
{
	int32 count = 0;
	for (size_t i = 0; i < Characters.Num(); ++i)
	{
		if (!Characters[i]->CharacterDead)
		{
			++count;
		}
	}

	return count;
}
