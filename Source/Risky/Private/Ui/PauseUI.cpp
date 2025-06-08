// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/PauseUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseUI::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddDynamic(this, &UPauseUI::ResumeGame);
	RestartButton->OnClicked.AddDynamic(this, &UPauseUI::RestartGame);
	OptionButton->OnClicked.AddDynamic(this, &UPauseUI::OpenOptions);
	MainMenuButton->OnClicked.AddDynamic(this, &UPauseUI::OpenMainMenu);
	QuitButton->OnClicked.AddDynamic(this, &UPauseUI::QuitGame);
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
