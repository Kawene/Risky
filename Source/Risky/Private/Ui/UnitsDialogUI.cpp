// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/UnitsDialogUI.h"
#include "Components/TextBlock.h"	
#include "Components/Slider.h"	
#include "Components/Button.h"	
#include "Character/PlayerCharacter.h"
#include "Ui/BaseButton.h"


void UUnitsDialogUI::NativeConstruct()
{
	Super::NativeConstruct();
	ActionButton->Button->OnClicked.AddDynamic(this, &UUnitsDialogUI::ButtonAction);
	CloseButton->Button->OnClicked.AddDynamic(this, &UUnitsDialogUI::ClosePopup);

	CloseButton->SetButtonText("X");
}

void UUnitsDialogUI::ButtonAction()
{
	Player->DialogAction(SliderUnits->GetValue());
	ClosePopup();
}

void UUnitsDialogUI::ClosePopup()
{
	SetVisibility(ESlateVisibility::Collapsed);
	Player->SetUiOpen(false);
	if (ParentWidget)
	{
		ParentWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUnitsDialogUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	SliderText->SetText(FText::AsNumber(SliderUnits->GetValue()));
}

void UUnitsDialogUI::ShowPopup(int32 MaxValue, FString textButton)  
{  
  SetVisibility(ESlateVisibility::Visible);  
  ActionButton->SetButtonText(MoveTemp(textButton));
  SliderUnits->SetMaxValue(MaxValue);  
  SliderUnits->SetValue(MaxValue);  
  Player->SetUiOpen(true);  
}

