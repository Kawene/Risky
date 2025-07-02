// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/ScoreboardUI.h"
#include <Kismet/GameplayStatics.h>
#include <Manager/TurnManager.h>
#include "Ui/PlayerInformationUI.h"
#include "Components/UniformGridPanel.h"
#include "Character/BaseCharacter.h"
#include "Region.h"

FPlayerInformationData* CreatePlayerInformation(ATurnManager* turnManager, ABaseCharacter* character)
{
	FPlayerInformationData* playerInfo = new FPlayerInformationData;
	for (ARegion* region : character->RegionsOwned)
	{
		playerInfo->UnitsAmountOwned += region->GetUnits();
	}
	playerInfo->RegionAmountOwned = character->RegionsOwned.Num();
	playerInfo->DeploymentAmount = turnManager->GetsNumberOfUnitsToDeploy(character);
	playerInfo->IsDead = character->CharacterDead;

	return playerInfo;
}

void UScoreboardUI::ShowScoreboard()
{
	if (!isInitialized)
	{
		isInitialized = true;
		InitializeGrid();
	}
	else {
		UpdateGridInformation();
	}

	SetVisibility(ESlateVisibility::Visible);
}

void UScoreboardUI::InitializeGrid()
{
	ATurnManager* turnManager = StaticCast<ATurnManager*>(UGameplayStatics::GetActorOfClass(GetWorld(), ATurnManager::StaticClass()));

	TArray<ABaseCharacter*> allPlayers = turnManager->Characters;

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	int row = 0;

	for (int32 i = 0; i < allPlayers.Num(); ++i) 
	{
		auto widget = CreateWidget<UPlayerInformationUI>(controller, PlayerInformationClass);

		FPlayerInformationData* playerInfo = CreatePlayerInformation(turnManager, allPlayers[i]);

		widget->InitializeData(
			allPlayers[i]->ColorIdentity,
			playerInfo);

		if (i % 3 == 0 && i != 0)
			++row;

		ScoreboardGrid->AddChildToUniformGrid(widget, row, i % 3);

		
	}
}

void UScoreboardUI::UpdateGridInformation()
{
	ATurnManager* turnManager = StaticCast<ATurnManager*>(UGameplayStatics::GetActorOfClass(GetWorld(), ATurnManager::StaticClass()));
	TArray<ABaseCharacter*> allPlayers = turnManager->Characters;


	for (int32 i = 0; i < ScoreboardGrid->GetChildrenCount(); ++i)
	{
		UPlayerInformationUI* playerInfoWidget = Cast<UPlayerInformationUI>(ScoreboardGrid->GetChildAt(i));
		if (!playerInfoWidget->IsPlayerDead())
		{
			FPlayerInformationData* playerInfo = CreatePlayerInformation(turnManager, allPlayers[i]);
			playerInfoWidget->UpdateInformation(playerInfo);
		}
	}
}

