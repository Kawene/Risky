// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/PauseUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Ui/BaseButton.h"
#include "Components/TextBlock.h"

void UPauseUI::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->Button->OnClicked.AddDynamic(this, &UPauseUI::ResumeGame);
	RestartButton->Button->OnClicked.AddDynamic(this, &UPauseUI::RestartGame);
	OptionButton->Button->OnClicked.AddDynamic(this, &UPauseUI::OpenOptions);
	MainMenuButton->Button->OnClicked.AddDynamic(this, &UPauseUI::OpenMainMenu);
	QuitButton->Button->OnClicked.AddDynamic(this, &UPauseUI::QuitGame);

	ResumeButton->SetButtonText("Resume");
	RestartButton->SetButtonText("Restart");
	OptionButton->SetButtonText("Options");
	MainMenuButton->SetButtonText("Main Menu");
	QuitButton->SetButtonText("Quit Game");
}


void UPauseUI::ResumeGame()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UPauseUI::RestartGame()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->ConsoleCommand("RestartLevel");
	}
}

void UPauseUI::OpenOptions()
{
}

void UPauseUI::OpenMainMenu()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		UGameplayStatics::OpenLevel(this, FName("MainMenu"));
	}
}

void UPauseUI::QuitGame()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->ConsoleCommand("quit");
	}
}
