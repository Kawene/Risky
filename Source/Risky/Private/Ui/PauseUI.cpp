// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/PauseUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Ui/BaseButton.h"
#include "Components/TextBlock.h"
#include "Ui/OptionsUI.h"
#include "Components/VerticalBox.h"

void UPauseUI::NativeConstruct()  
{  
	Super::NativeConstruct();  

	OptionButton->Button->OnClicked.AddDynamic(this, &UPauseUI::OpenOptions);  

	OptionButton->SetButtonText("Options");  

	OptionDialog->SetVisibility(ESlateVisibility::Hidden);
	OptionDialog->SetVisibility(ESlateVisibility::Collapsed);
	OptionDialog->Parent = PauseContainer;
}



void UPauseUI::OpenOptions()
{
	OptionDialog->SetVisibility(ESlateVisibility::Visible);
	PauseContainer->SetVisibility(ESlateVisibility::Hidden);
	PauseContainer->SetVisibility(ESlateVisibility::Collapsed);
}


