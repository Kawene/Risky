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
#include "AttackResults.h"


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
	ResultsData = Player->DeclareAttack(CurrentAttacking());

	if (UnitsToAttack->GetSelectedOption() == "Blitz")
	{
		ExecuteAttack();
		AttackResult1->SetText(FText::FromString(""));
		AttackResult2->SetText(FText::FromString(""));
		AttackResult3->SetText(FText::FromString(""));
		DefenceResult1->SetText(FText::FromString(""));
		DefenceResult2->SetText(FText::FromString(""));
		return;
	}

	AttackResult1->SetText(FText::FromString(FString::Printf(TEXT("%d"), ResultsData->AttackResult1)));

	if (ResultsData->AttackResult2 > 0)
	{
		AttackResult2->SetVisibility(ESlateVisibility::Visible);
		AttackResult2->SetText(FText::FromString(FString::Printf(TEXT("%d"), ResultsData->AttackResult2)));
	}
	else
		AttackResult2->SetVisibility(ESlateVisibility::Hidden);

	if (ResultsData->AttackResult3 > 0)
	{
		AttackResult3->SetVisibility(ESlateVisibility::Visible);
		AttackResult3->SetText(FText::FromString(FString::Printf(TEXT("%d"), ResultsData->AttackResult3)));
	}
	else
		AttackResult3->SetVisibility(ESlateVisibility::Hidden);

	DefenceResult1->SetText(FText::FromString(FString::Printf(TEXT("%d"), ResultsData->DefenceResult1)));

	if (ResultsData->DefenceResult2 > 0)
	{
		DefenceResult2->SetVisibility(ESlateVisibility::Visible);
		DefenceResult2->SetText(FText::FromString(FString::Printf(TEXT("%d"), ResultsData->DefenceResult2)));
	}
	else
		DefenceResult2->SetVisibility(ESlateVisibility::Hidden);


	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			GetWorld()->GetTimerManager().SetTimer(
				TimerHandle_DelayeAttack,
				this,
				&UAttackUI::ExecuteAttack,
				2.0f,
				false
			);
		});
	
}

void UAttackUI::ClosePopup()
{
	SetVisibility(ESlateVisibility::Collapsed);
	Player->SetUiOpen(false);
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

void UAttackUI::ExecuteAttack()
{
	Player->ApplyAttackResults(ResultsData);
}

void UAttackUI::ShowPopup(ARegion* attackingRegion, int32 enemyCount)
{
	Player->SetUiOpen(true);
	AttackingRegion = attackingRegion;

	if (enemyCount > 1)
		DefenceResult2->SetVisibility(ESlateVisibility::Visible);
	else 
		DefenceResult2->SetVisibility(ESlateVisibility::Hidden);
	
	CloseButton->SetIsEnabled(true);
	UpdateComboBoxOptions();
	SetVisibility(ESlateVisibility::Visible);
}
