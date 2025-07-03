// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/TurnTrackerUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

const FText DeploymentPhaseText = FText::FromString("Units to deploy :  ");
const FText AttackPhaseText = FText::FromString("Attack enemy regions");
const FText FortificationPhaseText = FText::FromString("Fortify your regions");


void UTurnTrackerUI::DeploymentInformation(int32 amountToDeploy)
{
	PhaseInformation->SetText(DeploymentPhaseText);
	NumberInformation->SetText(FText::AsNumber(amountToDeploy));
	PhaseIcon->SetBrushFromTexture(DeploymentIcon);
}

void UTurnTrackerUI::AttackInformation()
{
	PhaseInformation->SetText(AttackPhaseText);
	NumberInformation->SetText(FText::FromString(""));
	PhaseIcon->SetBrushFromTexture(AttackIcon);
}

void UTurnTrackerUI::FortificationInformation()
{
	PhaseInformation->SetText(FortificationPhaseText);
	NumberInformation->SetText(FText::FromString(""));
	PhaseIcon->SetBrushFromTexture(FortificationIcon);
}
