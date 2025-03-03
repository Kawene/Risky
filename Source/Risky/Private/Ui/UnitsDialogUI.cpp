// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/UnitsDialogUI.h"
#include "Components/TextBlock.h"	
#include "Components/Slider.h"	
#include "Components/Button.h"	
#include "Character/PlayerCharacter.h"


void UUnitsDialogUI::NativeConstruct()
{
	Super::NativeConstruct();
	ActionButton->OnClicked.AddDynamic(this, &UUnitsDialogUI::ButtonAction);
	CloseButton->OnClicked.AddDynamic(this, &UUnitsDialogUI::ClosePopup);
}

void UUnitsDialogUI::ButtonAction()
{
	Player->DialogAction(SliderUnits->GetValue());
	ClosePopup();
}

void UUnitsDialogUI::ClosePopup()
{
	SetVisibility(ESlateVisibility::Collapsed);
	if (ParentWidget)
	{
		ParentWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUnitsDialogUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	SliderText->SetText(FText::AsNumber(SliderUnits->GetValue()));
}

void UUnitsDialogUI::ShowPopup(int32 MaxValue, FText textButton)
{
	SetVisibility(ESlateVisibility::Visible);
	ActionButtonText->SetText(textButton);
	SliderUnits->SetMaxValue(MaxValue);
	SliderUnits->SetValue(MaxValue);
}

