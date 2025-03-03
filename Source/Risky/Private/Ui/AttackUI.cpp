// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/AttackUI.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Character/PlayerCharacter.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Math/UnrealMathUtility.h"
#include "UI/UnitsDialogUI.h"
#include "Region.h"


void UAttackUI::NativeConstruct()
{
	Super::NativeConstruct();
	AttackButton->OnClicked.AddDynamic(this, &UAttackUI::Attack);
	CloseButton->OnClicked.AddDynamic(this, &UAttackUI::ClosePopup);
	Player->AttackStep.BindUObject(this, &UAttackUI::UpdateUI);

	TransferSection->CloseButton->SetVisibility(ESlateVisibility::Collapsed);
	TransferSection->CloseButtonText->SetVisibility(ESlateVisibility::Collapsed);
	TransferSection->SetVisibility(ESlateVisibility::Collapsed);
	TransferSection->Player = Player;
	TransferSection->ParentWidget = this;
}

void UAttackUI::Attack()
{
	Player->AttackSelectedRegion(CurrentAttacking());
}

void UAttackUI::ClosePopup()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UAttackUI::UpdateUI(bool regionCaptured)
{
	if (regionCaptured)
	{
		if (CurrentAttacking() < 4 && CurrentAttacking() == AttackingRegion->GetUnits() - 1)
		{
			Player->TransferAmount(AttackingRegion->GetUnits() - 1);
			ClosePopup();
			return;
		}
		CloseButton->SetIsEnabled(false);
		TransferSection->ShowPopup(AttackingRegion->GetUnits() - 1, FText::FromString("Transfer"));
		TransferSection->SliderUnits->SetMinValue(FMath::Min(3, CurrentAttacking()));
		return;
	}

	int32 remainingUnits = AttackingRegion->GetUnits() - 1;
	if (remainingUnits == 0)
	{
		ClosePopup();
	}
	else if (UnitsToAttack->GetSelectedOption() == "Blitz") {
		Attack();
	}
	else {
		UpdateComboBoxOptions();
	}
}

int32 UAttackUI::CurrentAttacking()
{
	int32 attacker = 0;
	FString value = UnitsToAttack->GetSelectedOption();
	if (value == "Blitz")
	{
		attacker = AttackingRegion->GetUnits() - 1;
	}
	else {
		attacker = FCString::Atoi(*value);
	}
	return attacker;
}

void UAttackUI::UpdateComboBoxOptions()
{
	int32 remainingUnits = AttackingRegion->GetUnits() - 1;

	FString itemSelected = UnitsToAttack->GetSelectedOption();

	UnitsToAttack->ClearOptions();
	UnitsToAttack->AddOption(FString("Blitz"));
	UnitsToAttack->SetSelectedOption(FString("Blitz"));

	if (remainingUnits > 2)
	{
		UnitsToAttack->AddOption(FString("3"));
		UnitsToAttack->AddOption(FString("2"));
	}
	else if (remainingUnits == 2)
	{
		UnitsToAttack->AddOption(FString("2"));
	}

	UnitsToAttack->AddOption(FString("1"));

	UnitsToAttack->SetSelectedOption(itemSelected);
}

void UAttackUI::ShowPopup(ARegion* attackingRegion)
{
	AttackingRegion = attackingRegion;
	CloseButton->SetIsEnabled(true);
	UpdateComboBoxOptions();
	SetVisibility(ESlateVisibility::Visible);
}
