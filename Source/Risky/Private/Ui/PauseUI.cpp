// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/PauseUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Ui/BaseButton.h"
#include "Components/TextBlock.h"

void UPauseUI::NativeConstruct()
{
	Super::NativeConstruct();

	OptionButton->Button->OnClicked.AddDynamic(this, &UPauseUI::OpenOptions);

	OptionButton->SetButtonText("Options");

}



void UPauseUI::OpenOptions()
{
}


