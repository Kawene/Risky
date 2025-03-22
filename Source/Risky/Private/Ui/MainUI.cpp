// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/MainUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Character/PlayerCharacter.h"
#include "Ui/UnitsDialogUI.h"
#include "Ui/AttackUI.h"
#include "Risky/RiskyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/TurnManager.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	InteractButton->OnClicked.AddDynamic(this, &UMainUI::OnButtonClick);
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
}

void UMainUI::ShowUnitsUi(int32 maxUnit, FText textButton)
{
	UnitsDialog->ShowPopup(maxUnit, textButton);
}

void UMainUI::ShowAttackUi(ARegion* region)
{
	AttackDialog->ShowPopup(region);
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
		InteractText->SetText(FText::FromString("Fortification"));
		break;
	case EGamePhase::FortificationPhase:
		InteractText->SetText(FText::FromString("End Turn"));
		break;
	case EGamePhase::NotCurrentTurn:
		auto turnManager = StaticCast<ATurnManager*>(UGameplayStatics::GetActorOfClass(GetWorld(), ATurnManager::StaticClass()));
		switch (turnManager->AiPhasesSteps)
		{
		case EAiPhasesSteps::ByPhases:
			InteractText->SetText(FText::FromString("Next Phase"));
			break;
		case EAiPhasesSteps::ByTurn:
			InteractText->SetText(FText::FromString("Next Turn"));
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
