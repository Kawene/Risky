// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/VictoryUI.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Ui/BaseButton.h"
#include "Components/TextBlock.h"

void UVictoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	RestartButton->Button->OnClicked.AddDynamic(this, &UVictoryUI::RestartGame);
	MainMenuButton->Button->OnClicked.AddDynamic(this, &UVictoryUI::OpenMainMenu);
	QuitButton->Button->OnClicked.AddDynamic(this, &UVictoryUI::QuitGame);

	RestartButton->SetButtonText("Restart");
	MainMenuButton->SetButtonText("Main Menu");
	QuitButton->SetButtonText("Quit Game");
}

void UVictoryUI::RestartGame()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->ConsoleCommand("RestartLevel");
	}
}

void UVictoryUI::OpenMainMenu()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		UGameplayStatics::OpenLevel(this, FName("MainMenu"));
	}
}

void UVictoryUI::QuitGame()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->ConsoleCommand("quit");
	}
}
