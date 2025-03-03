// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttackUI.generated.h"


UCLASS()
class RISKY_API UAttackUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UComboBoxString* UnitsToAttack;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* AttackButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* AttackButtonText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CloseButtonText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UUnitsDialogUI* TransferSection;

	UPROPERTY()
	class ARegion* AttackingRegion;

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void ClosePopup();

	UFUNCTION()
	void UpdateUI(bool regionCaptured);

	int32 CurrentAttacking();

	void UpdateComboBoxOptions();

public:

	void ShowPopup(ARegion* attackingRegion);

	virtual void  NativeConstruct();

	class APlayerCharacter* Player;

};
