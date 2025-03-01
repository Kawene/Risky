// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/MainUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Character/PlayerCharacter.h"
#include "Ui/DeploymentUI.h"
#include "Ui/AttackUI.h"
#include "Ui/FortificationUI.h"
#include "Risky/RiskyPlayerController.h"

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

	DeploymentDialog = CreateWidget<UDeploymentUI>(controller, DeploymentHUDClass);
	DeploymentDialog->Player = player;
	DeploymentDialog->AddToPlayerScreen();
	DeploymentDialog->SetVisibility(ESlateVisibility::Hidden);

	AttackDialog = CreateWidget<UAttackUI>(controller, AttackHUDClass);
	AttackDialog->Player = player;
	AttackDialog->AddToPlayerScreen();
	AttackDialog->SetVisibility(ESlateVisibility::Hidden);
}

void UMainUI::ShowDeployUi(int32 maxUnit)
{
	DeploymentDialog->ShowPopup(maxUnit);
}

void UMainUI::ShowAttackUi(ARegion* region)
{
	AttackDialog->ShowPopup(region);
}

void UMainUI::ShowFortificationUi()
{
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
		InteractText->SetText(FText::FromString("Attack"));
		SetVisibility(ESlateVisibility::Visible);
		break;
	case EGamePhase::AttackPhase:
		InteractText->SetText(FText::FromString("Fortification"));
		break;
	case EGamePhase::FortificationPhase:
		InteractText->SetText(FText::FromString("End Turn"));
		break;
	case EGamePhase::NotCurrentTurn:
		SetVisibility(ESlateVisibility::Hidden);
		break;
	}
}
