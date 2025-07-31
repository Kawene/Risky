// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/MainUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Character/PlayerCharacter.h"
#include "Ui/UnitsDialogUI.h"
#include "Ui/AttackUI.h"
#include "Ui/PauseUI.h"
#include "Ui/ScoreboardUI.h"
#include "Ui/PlayerCardsUI.h"
#include "Risky/RiskyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/TurnManager.h"
#include "Ui/BaseButton.h"
#include "Province.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	InteractButton->Button->OnClicked.AddDynamic(this, &UMainUI::OnButtonClick);

	ProvinceButton->OnClicked.AddDynamic(this, &UMainUI::ToggleProvincesDetails);

	CardButton->OnClicked.AddDynamic(this, &UMainUI::ShowCardsUi);
}

void UMainUI::InitializeUI(APlayerCharacter* player, ARiskyPlayerController* controller)
{
	Player = player;
	AddToPlayerScreen();
	ButtonVisibility(false);

	TArray<AActor*> provincesActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProvince::StaticClass(), provincesActors);

	for (AActor* actor : provincesActors)
	{
		Provinces.Add(Cast<AProvince>(actor));
	}

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
	PauseDialog->MainUIReference = this;

	VictoryDialog = CreateWidget<UVictoryUI>(controller, VictoryHUDClass);
	VictoryDialog->AddToPlayerScreen();
	VictoryDialog->SetVisibility(ESlateVisibility::Hidden);

	DefeatDialog = CreateWidget<UDefeatUI>(controller, DefeatHUDClass);
	DefeatDialog->AddToPlayerScreen();
	DefeatDialog->SetVisibility(ESlateVisibility::Hidden);

	ScoreboardDialog = CreateWidget<UScoreboardUI>(controller, ScoreboardHUDClass);
	ScoreboardDialog->AddToPlayerScreen(1);
	ScoreboardDialog->SetVisibility(ESlateVisibility::Hidden);

	PlayerCardsDialog = CreateWidget<UPlayerCardsUI>(controller, PlayerCardsHUDClass);
	PlayerCardsDialog->AddToPlayerScreen(1);
	PlayerCardsDialog->SetVisibility(ESlateVisibility::Hidden);
	PlayerCardsDialog->MainUIReference = this;
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

void UMainUI::ShowCardsUi()
{
	if (!UiOpen)
	{
		UiOpen = true;
		PlayerCardsDialog->ShowCardsList();
	}
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
	else if (ProvincesDetails) {
		ToggleProvincesDetails();
	} 
	else if (PlayerCardsDialog->IsVisible()) {
		CloseCardsUi();
	}
}

void UMainUI::CloseCardsUi()
{
	PlayerCardsDialog->HideCardsList();
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

void UMainUI::AddCardToUi(FCard* card)
{
	PlayerCardsDialog->AddCard(card);	
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
		ButtonVisibility(false);
		break;
	case EGamePhase::AttackPhase:
		ButtonVisibility(true);
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
			ButtonVisibility(false);
			break;
		default:
			break;
		}
		break;
	}
}

void UMainUI::ToggleProvincesDetails()
{
	if (ProvincesDetails)
	{
		for (AProvince* province : Provinces)
		{
			province->HideDetails();
		}
		ProvincesDetails = false;
		UiOpen = false;
		Player->DeZoomCamera();
	}
	else
	{
		for (AProvince* province : Provinces)
		{
			province->ViewDetails();
		}
		ProvincesDetails = true;
		UiOpen = true;
		Player->SetCameraToSeeMap();
	}
}
