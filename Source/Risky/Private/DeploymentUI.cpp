// Fill out your copyright notice in the Description page of Project Settings.


#include "DeploymentUI.h"
#include "Components/TextBlock.h"	
#include "Components/Slider.h"	
#include "Components/Button.h"	
#include "PlayerCharacter.h"


void UDeploymentUI::NativeConstruct()
{
	Super::NativeConstruct();
	DeployButton->OnClicked.AddDynamic(this, &UDeploymentUI::DeployUnits);
}

void UDeploymentUI::DeployUnits()
{
	Player->DeployUnitsToSelectedRegion(SliderUnits->Value);
	SetVisibility(ESlateVisibility::Collapsed);
}

void UDeploymentUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	SliderText->SetText(FText::AsNumber(SliderUnits->Value));
}

void UDeploymentUI::ShowPopup(int32 MaxValue)
{
	SetVisibility(ESlateVisibility::Visible);
	SliderUnits->SetMaxValue(MaxValue);
	SliderUnits->SetValue(MaxValue);
}
