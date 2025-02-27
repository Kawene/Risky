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

	DeploymentDialog = CreateWidget<UDeploymentUI>(controller, DeploymentHUDClass);
	DeploymentDialog->Player = player;
	DeploymentDialog->AddToPlayerScreen();
	DeploymentDialog->SetVisibility(ESlateVisibility::Hidden);
}

void UMainUI::ShowDeployUi()
{
	DeploymentDialog->ShowPopup(3);
}

void UMainUI::ShowAttackUi()
{
}

void UMainUI::ShowFortificationUi()
{
}

void UMainUI::OnButtonClick()
{
	Player->FinishedCurrentPhase();
}
