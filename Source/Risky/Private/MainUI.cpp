// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PlayerCharacter.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	InteractButton->OnClicked.AddDynamic(this, &UMainUI::OnButtonClick);
}

void UMainUI::OnButtonClick()
{
	Player->FinishedCurrentPhase();
}
