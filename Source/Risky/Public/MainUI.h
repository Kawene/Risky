// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

class ARiskyPlayerController;
class APlayerCharacter;

UCLASS()
class RISKY_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void  NativeConstruct();

	void InitializeUI(APlayerCharacter* player, ARiskyPlayerController* controller);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* InteractButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* InteractText;

	APlayerCharacter* Player;

	void ShowDeployUi();

	void ShowAttackUi();

	void ShowFortificationUi();

private:
	UFUNCTION()
	void OnButtonClick();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDeploymentUI> DeploymentHUDClass;

	UPROPERTY()
	class UDeploymentUI* DeploymentDialog;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAttackUI> AttackHUDClass;

	UPROPERTY()
	class UAttackUI* AttackDialog;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UFortificationUI> FortificationHUDClass;

	UPROPERTY()
	class UFortificationUI* FortificationDialog;
};
