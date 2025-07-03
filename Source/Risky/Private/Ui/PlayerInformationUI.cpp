// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/PlayerInformationUI.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Manager/TurnManager.h"
#include "Character/BaseCharacter.h"
#include "Region.h"

void UPlayerInformationUI::InitializeData(FColor color, FPlayerInformationData* playerInformation)
{
	FVector newColor = FVector(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f);

	PlayerColor->SetColorAndOpacity(FLinearColor(newColor));
	UpdateInformation(playerInformation);

	DeathSign->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerInformationUI::UpdateInformation(FPlayerInformationData* playerInformation)
{
	if (PlayerDead)
		return;

	if (playerInformation->IsDead)
	{
		PlayerDied();
		return;
	}

	UnitsAmountOwned->SetText(FText::AsNumber(playerInformation->UnitsAmountOwned));	
	RegionAmountOwned->SetText(FText::AsNumber(playerInformation->RegionAmountOwned));
	DeploymentAmount->SetText(FText::AsNumber(playerInformation->DeploymentAmount));
}

void UPlayerInformationUI::PlayerDied()
{
	PlayerDead = true;
	DeathSign->SetVisibility(ESlateVisibility::Visible);
	UnitsAmountOwned->SetText(FText::FromString("0"));
	RegionAmountOwned->SetText(FText::FromString("0"));
	DeploymentAmount->SetText(FText::FromString("0"));
}

FPlayerInformationData::FPlayerInformationData()
{
}

FPlayerInformationData::FPlayerInformationData(ATurnManager* turnManager, ABaseCharacter* character)
{	
	for (auto region : character->RegionsOwned)
	{
		UnitsAmountOwned += region->GetUnits();
	}
	RegionAmountOwned = character->RegionsOwned.Num();
	DeploymentAmount = turnManager->GetsNumberOfUnitsToDeploy(character);
	IsDead = character->CharacterDead;	
}
