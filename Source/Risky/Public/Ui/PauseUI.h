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
	class UButton* ResumeButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* RestartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* OptionButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitButton;

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
