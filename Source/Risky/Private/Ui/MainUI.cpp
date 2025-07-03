// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/MainUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Character/PlayerCharacter.h"
#include "Ui/UnitsDialogUI.h"
#include "Ui/AttackUI.h"
#include "Ui/PauseUI.h"
#include "Ui/ScoreboardUI.h"
#include "Risky/RiskyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/TurnManager.h"
#include "Ui/BaseButton.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	InteractButton->Button->OnClicked.AddDynamic(this, &UMainUI::OnButtonClick);
}

void UMainUI::InitializeUI(APlayerCharacter* player, ARiskyPlayerController* controller)
{
	Player = player;
	AddToPlayerScreen();
	SetVisibility(ESlateVisibility::Hidden);

	Player->ChangeGamePhase.BindUObject(this, &UMainUI::OnGamePhaseChange);

	UnitsDialog = CreateWidget<UUnitsDialogUI>(controller, UnitsHUDClass);
	UnitsDialog->Player = player;
	UnitsDialog->AddToPlayerScreen();
	UnitsDialog->SetVisibility(ESlateVisibility::Hidden);

	AttackDialog = CreateWidget<UAttackUI>(controller, AttackHUDClass);
	AttackDialog->Player = player;
	AttackDialog->AddToPlayerScreen();
	AttackDialog->SetVisibility(ESlateVisibility::Hidden);


	PauseDialog = CreateWidget<UPauseUI>(controller, PauseHUDClass);
	PauseDialog->AddToPlayerScreen(2);
	PauseDialog->SetVisibility(ESlateVisibility::Hidden);

	VictoryDialog = CreateWidget<UVictoryUI>(controller, VictoryHUDClass);
	VictoryDialog->AddToPlayerScreen();
	VictoryDialog->SetVisibility(ESlateVisibility::Hidden);

	DefeatDialog = CreateWidget<UDefeatUI>(controller, DefeatHUDClass);
	DefeatDialog->AddToPlayerScreen();
	DefeatDialog->SetVisibility(ESlateVisibility::Hidden);

	ScoreboardDialog = CreateWidget<UScoreboardUI>(controller, ScoreboardHUDClass);
	ScoreboardDialog->AddToPlayerScreen(1);
	ScoreboardDialog->SetVisibility(ESlateVisibility::Hidden);
}

void UMainUI::ShowUnitsUi(int32 maxUnit, FText textButton)
{
	if (!UiOpen)
	{
		UiOpen = true;
		UnitsDialog->ShowPopup(maxUnit, textButton.ToString());
	}
}

void UMainUI::ShowAttackUi(ARegion* region, int32 enemyCount, FColor enemyColor)
{
	if (!UiOpen)
	{
		UiOpen = true;
		AttackDialog->ShowPopup(region, enemyCount, enemyColor);
	}
}

void UMainUI::ToggleVisibilityPauseUi()
{
	if (PauseDialog->IsVisible())
	{
		UiOpen = false;
		PauseDialog->SetVisibility(ESlateVisibility::Hidden);		
	}
	else if (!UiOpen)
	{
		PauseDialog->ShowPopup();
		UiOpen = true;
	}
}

void UMainUI::ToggleVisibilityScoreboardUi()
{
	if (ScoreboardDialog->IsVisible())
	{
		UiOpen = false;
		ScoreboardDialog->SetVisibility(ESlateVisibility::Hidden);
	}
	else if(!UiOpen)
	{
		UiOpen = true;
		ScoreboardDialog->ShowScoreboard();
	}
}

void UMainUI::ShowVictoryUi()
{
	UiOpen = true;
	VictoryDialog->ShowPopup();	
}

void UMainUI::ShowDefeatUi()
{
	UiOpen = true;
	DefeatDialog->ShowPopup();
}

void UMainUI::CloseUnitsUi()
{
	UiOpen = false;
	UnitsDialog->ClosePopup();
}

void UMainUI::CloseAttackUi()
{
	UiOpen = false;
	AttackDialog->ClosePopup();
}

void UMainUI::CloseCurrentUi()
{
	if (UnitsDialog->IsVisible())
	{
		CloseUnitsUi();
	}
	else if (AttackDialog->IsVisible()) {
		CloseAttackUi();
	}
	else if (PauseDialog->IsVisible())
	{
		ToggleVisibilityPauseUi();
	}
	else if (ScoreboardDialog->IsVisible())
	{
		ToggleVisibilityScoreboardUi();
	}
}

void UMainUI::UiHasClosed()
{
	UiOpen = false;
}

void UMainUI::ButtonVisibility(bool visible)
{
	if (visible)
		InteractButton->SetVisibility(ESlateVisibility::Visible);
	else
		InteractButton->SetVisibility(ESlateVisibility::Hidden);
}

void UMainUI::OnButtonClick()
{
	Player->FinishedCurrentPhase();
}

void UMainUI::OnGamePhaseChange(EGamePhase gamePhase)
{
	switch (gamePhase)
	{
	case EGamePhase::DeploymentPhase:	
		SetVisibility(ESlateVisibility::Hidden);
		break;
	case EGamePhase::AttackPhase:
		SetVisibility(ESlateVisibility::Visible);
		InteractButton->SetButtonText("Fortification");
		break;
	case EGamePhase::FortificationPhase:
		InteractButton->SetButtonText("End Turn");
		break;
	case EGamePhase::NotCurrentTurn:
		auto turnManager = StaticCast<ATurnManager*>(UGameplayStatics::GetActorOfClass(GetWorld(), ATurnManager::StaticClass()));
		switch (turnManager->AiPhasesSteps)
		{
		case EAiPhasesSteps::ByPhases:
			InteractButton->SetButtonText("Next Phase");
			break;
		case EAiPhasesSteps::ByTurn:
			InteractButton->SetButtonText("Next Turn");
			break;
		case EAiPhasesSteps::NoStop:
			SetVisibility(ESlateVisibility::Hidden);
			break;
		default:
			break;
		}
		break;
	}
}
