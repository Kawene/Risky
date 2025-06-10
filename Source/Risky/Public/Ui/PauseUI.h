// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseUI.generated.h"


UCLASS()
class RISKY_API UPauseUI : public UUserWidget
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* ResumeButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* RestartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* OptionButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* MainMenuButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* QuitButton;

	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void OpenOptions();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void QuitGame();

public:
	virtual void  NativeConstruct();
};
