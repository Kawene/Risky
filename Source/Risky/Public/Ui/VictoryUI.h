// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VictoryUI.generated.h"

UCLASS()
class RISKY_API UVictoryUI : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* RestartButton;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* MainMenuButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* QuitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* OpenSound;

	UFUNCTION()
	void RestartGame();


	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void QuitGame();

public:
	virtual void  NativeConstruct();

	void ShowPopup();
	
};
