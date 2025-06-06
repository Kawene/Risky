// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonWidgetCarousel.h"
#include "Blueprint/UserWidget.h"
#include "AttackUI.generated.h"


UCLASS()
class RISKY_API UAttackUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UUnitsDialogUI* TransferSection;

	UPROPERTY()
	class ARegion* AttackingRegion;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* AttackResult1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* AttackResult2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* AttackResult3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* DefenceResult1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* DefenceResult2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UVerticalBox* ResultsAttack;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UVerticalBox* ResultsDefence;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHorizontalBox* Carousel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCommonWidgetCarousel* AttackChoice;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LeftButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* RightButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* OptionBlitz;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Option1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Option2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Option3;

	UFUNCTION()
	void BlitzSelected();

	UFUNCTION()
	void OneSelected();

	UFUNCTION()
	void TwoSelected();

	UFUNCTION()
	void ThreeSelected();

	FTimerHandle TimerHandle_DelayeAttack;

	struct FAttackResults* ResultsData;

	UFUNCTION()
	void Attack(int32 attackingAmount);

	UFUNCTION()
	void UpdateUI(bool regionCaptured);

	int32 CurrentAttacking();

	void ExecuteAttack();

	UFUNCTION()
	void LeftCarouselAction();

	UFUNCTION()
	void RightCarouselAction();

public:

	UFUNCTION()
	void ClosePopup();

	void ShowPopup(ARegion* attackingRegion, int32 enemyCount);

	virtual void  NativeConstruct();

	class APlayerCharacter* Player;

};
