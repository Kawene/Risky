// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/AttackUI.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Character/PlayerCharacter.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Math/UnrealMathUtility.h"
#include "UI/UnitsDialogUI.h"
#include "Region.h"
#include "AttackResults.h"
#include "CommonWidgetCarousel.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"

void UAttackUI::NativeConstruct()  
{  
   Super::NativeConstruct();  

   Player->AttackStep.BindUObject(this, &UAttackUI::UpdateUI);  

   LeftButton->OnClicked.AddDynamic(this, &UAttackUI::LeftCarouselAction);  
   RightButton->OnClicked.AddDynamic(this, &UAttackUI::RightCarouselAction);  

   AttackChoice->OnCurrentPageIndexChanged.AddDynamic(this, &UAttackUI::OnChoiceChange);  

   OptionBlitz->OnMouseButtonDownEvent.BindUFunction(this, FName("BlitzSelected"));  
   Option1->OnMouseButtonDownEvent.BindUFunction(this, FName("OneSelected"));  
   Option2->OnMouseButtonDownEvent.BindUFunction(this, FName("TwoSelected"));  
   Option3->OnMouseButtonDownEvent.BindUFunction(this, FName("ThreeSelected"));  

   TransferSection->CloseButton->SetVisibility(ESlateVisibility::Collapsed);  
   TransferSection->CloseButtonText->SetVisibility(ESlateVisibility::Collapsed);  
   TransferSection->SetVisibility(ESlateVisibility::Collapsed);  
   TransferSection->Player = Player;  
   TransferSection->ParentWidget = this;  
}

void UAttackUI::BlitzSelected()
{
	Attack(AttackingRegion->GetUnits() - 1);
}

void UAttackUI::OneSelected()
{
	Attack(1);
}

void UAttackUI::TwoSelected()
{
	Attack(2);
}

void UAttackUI::ThreeSelected()
{
	Attack(3);
}

void UAttackUI::OnChoiceChange(UCommonWidgetCarousel* widgetCarousel, int32 newPageIndex)
{
	int32 maxAttakingAmmount = AttackingRegion->GetUnits() - 1;
	switch (newPageIndex)
	{
	case 0:
		if (maxAttakingAmmount >= 3)
		{
			AttackResult1->SetVisibility(ESlateVisibility::Visible);
			AttackResult2->SetVisibility(ESlateVisibility::Visible);
			AttackResult3->SetVisibility(ESlateVisibility::Visible);
		}
		else if (maxAttakingAmmount >= 2)
		{
			AttackResult1->SetVisibility(ESlateVisibility::Visible);
			AttackResult2->SetVisibility(ESlateVisibility::Visible);
			AttackResult3->SetVisibility(ESlateVisibility::Hidden);
		}
		else 
		{
			AttackResult1->SetVisibility(ESlateVisibility::Visible);
			AttackResult2->SetVisibility(ESlateVisibility::Hidden);
			AttackResult3->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case 1:
		AttackResult1->SetVisibility(ESlateVisibility::Visible);
		AttackResult2->SetVisibility(ESlateVisibility::Hidden);
		AttackResult3->SetVisibility(ESlateVisibility::Hidden);
		break;
	case 2:
		AttackResult1->SetVisibility(ESlateVisibility::Visible);
		AttackResult2->SetVisibility(ESlateVisibility::Visible);
		AttackResult3->SetVisibility(ESlateVisibility::Hidden);
		break;
	case 3:
		AttackResult1->SetVisibility(ESlateVisibility::Visible);
		AttackResult2->SetVisibility(ESlateVisibility::Visible);
		AttackResult3->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}

void UAttackUI::Attack(int32 attackingAmount)
{
	VisualRandomize = false;

	ResultsData = Player->DeclareAttack(attackingAmount);

	if (AttackChoice->GetActiveWidgetIndex() == 0)
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
	if (!TransferSection->IsVisible())
	{
		SetVisibility(ESlateVisibility::Collapsed);
		Player->SetUiOpen(false);
	}
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
		TransferSection->ShowPopup(AttackingRegion->GetUnits() - 1, FText::FromString("Transfer"));
		TransferSection->SliderUnits->SetMinValue(FMath::Min(3, CurrentAttacking()));
		Carousel->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	int32 remainingUnits = AttackingRegion->GetUnits() - 1;
	if (remainingUnits == 0)
	{
		ClosePopup();
	}
	else if (AttackChoice->GetActiveWidgetIndex() == 0) {
		BlitzSelected();
	}

}

int32 UAttackUI::CurrentAttacking()
{
	int32 attacker = 0;
	int32 value = AttackChoice->GetActiveWidgetIndex();
	if (value == 0)
	{
		attacker = AttackingRegion->GetUnits() - 1;
	}
	else {
		attacker = value;
	}
	return attacker;
}

void UAttackUI::ExecuteAttack()
{
	int32 remainingDefenders = Player->ApplyAttackResults(ResultsData);

	if (remainingDefenders == 1)
	{
		DefenceResult2->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UAttackUI::LeftCarouselAction()
{
	VisualRandomize = true;

	int32 remainingUnits = AttackingRegion->GetUnits() - 1;

	if (remainingUnits >= 3 || AttackChoice->GetActiveWidgetIndex() != 0)
	{
		AttackChoice->NextPage();
		return;
	}

	if (remainingUnits == 2)
		AttackChoice->SetActiveWidgetIndex(2);
	else 
		AttackChoice->PreviousPage();
}

void UAttackUI::RightCarouselAction()
{
	VisualRandomize = true;
	int32 remainingUnits = AttackingRegion->GetUnits() - 1;

	if (remainingUnits >= 3)
	{
		AttackChoice->PreviousPage();
		return;
	}


	if (AttackChoice->GetActiveWidgetIndex() == 1 && remainingUnits == 1)
		AttackChoice->NextPage();
	else if(AttackChoice->GetActiveWidgetIndex() == 2) 
		AttackChoice->SetActiveWidgetIndex(0);
	else 
		AttackChoice->PreviousPage();
}

void UAttackUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	DisplayTimeDelay += InDeltaTime;

	if (VisualRandomize)
	{
		float min = 0.5f;
		float max = 0.53f;
		float randomChange = FMath::FRandRange(min, max);
		if (DisplayTimeDelay > randomChange)
			AttackResult1->SetText(FText::AsNumber(FMath::RandRange(1, 6)));
		
		randomChange = FMath::FRandRange(min, max);
		if (DisplayTimeDelay > randomChange)
			AttackResult2->SetText(FText::AsNumber(FMath::RandRange(1, 6)));

		randomChange = FMath::FRandRange(min, max);
		if (DisplayTimeDelay > randomChange)
			AttackResult3->SetText(FText::AsNumber(FMath::RandRange(1, 6)));

		randomChange = FMath::FRandRange(min, max);
		if (DisplayTimeDelay > randomChange)
			DefenceResult1->SetText(FText::AsNumber(FMath::RandRange(1, 6)));

		randomChange = FMath::FRandRange(min, max);
		if (DisplayTimeDelay > randomChange)
			DefenceResult2->SetText(FText::AsNumber(FMath::RandRange(1, 6)));

		if (DisplayTimeDelay > max)
			DisplayTimeDelay -= max;
	}
}

void UAttackUI::ShowPopup(ARegion* attackingRegion, int32 enemyCount, FColor enemyColor)
{
	Player->SetUiOpen(true);
	AttackingRegion = attackingRegion;

	if (enemyCount > 1)
		DefenceResult2->SetVisibility(ESlateVisibility::Visible);
	else 
		DefenceResult2->SetVisibility(ESlateVisibility::Hidden);
	
	SetVisibility(ESlateVisibility::Visible);
	Carousel->SetVisibility(ESlateVisibility::Visible);
	OnChoiceChange(AttackChoice, AttackChoice->GetActiveWidgetIndex());

	DefenceBackground->SetBrushColor(enemyColor.ReinterpretAsLinear());
	AttackBackground->SetBrushColor(Player->ColorIdentity.ReinterpretAsLinear());

	VisualRandomize = true;

}
