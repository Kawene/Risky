// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/AttackUI.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Character/PlayerCharacter.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Region.h"


void UAttackUI::NativeConstruct()
{
	Super::NativeConstruct();
	AttackButton->OnClicked.AddDynamic(this, &UAttackUI::Attack);
	CloseButton->OnClicked.AddDynamic(this, &UAttackUI::ClosePopup);
	TransferButton->OnClicked.AddDynamic(this, &UAttackUI::TransferUnits);
	Player->AttackStep.BindUObject(this, &UAttackUI::UpdateUI);
	TranferSection->SetVisibility(ESlateVisibility::Collapsed);
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
		if (CurrentAttacking() == AttackingRegion->GetUnits() - 1)
		{
			Player->TransferAmount(AttackingRegion->GetUnits() - 1);
			ClosePopup();
			return;
		}
		CloseButton->SetIsEnabled(false);
		TranferSection->SetVisibility(ESlateVisibility::Visible);
		SliderUnits->SetMinValue(CurrentAttacking());
		SliderUnits->SetMaxValue(AttackingRegion->GetUnits() - 1);
		SliderUnits->SetValue(SliderUnits->MaxValue);
		return;
	}

	int32 remainingUnits = AttackingRegion->GetUnits() - 1;
	if (remainingUnits == 0)
	{
		ClosePopup();
	}
	else {
		UnitsToAttack->ClearOptions();
		UnitsToAttack->AddOption(FString("Blitz"));
		UnitsToAttack->SetSelectedOption(FString("Blitz"));

		if (remainingUnits > 2)
		{
			UnitsToAttack->AddOption(FString("3"));
			UnitsToAttack->AddOption(FString("2"));
		}
		else if (remainingUnits == 2 )
		{
			UnitsToAttack->AddOption(FString("2"));
		}

		UnitsToAttack->AddOption(FString("1"));
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

void UAttackUI::TransferUnits()
{
	ClosePopup();
	Player->TransferAmount(SliderUnits->GetValue());
}

void UAttackUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	SliderText->SetText(FText::AsNumber(SliderUnits->GetValue()));
}

void UAttackUI::ShowPopup(ARegion* attackingRegion)
{
	AttackingRegion = attackingRegion;
	CloseButton->SetIsEnabled(true);
	UpdateUI(false);
	SetVisibility(ESlateVisibility::Visible);
}
