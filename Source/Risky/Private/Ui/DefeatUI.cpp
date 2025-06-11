// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/DefeatUI.h"
#include "Ui/BaseButton.h"
#include "Components/Button.h"

void UDefeatUI::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->Button->OnClicked.AddDynamic(this, &UDefeatUI::ResumeGame);

	ResumeButton->SetButtonText("Resume");
}


void UDefeatUI::ResumeGame()
{
	SetVisibility(ESlateVisibility::Hidden);
}

