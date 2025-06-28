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
	class UHorizontalBox* Carousel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCommonWidgetCarousel* AttackChoice;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LeftButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* RightButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* OptionBlitz;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Option1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Option2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Option3;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBorder* DefenceBackground;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBorder* AttackBackground;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* AttackAnim1Won;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* AttackAnim2Won;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* DefenceAnim1Won;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* DefenceAnim2Won;

	UFUNCTION()
	void BlitzSelected();

	UFUNCTION()
	void OneSelected();

	UFUNCTION()
	void TwoSelected();

	UFUNCTION()
	void ThreeSelected();

	UFUNCTION()
	void OnChoiceChange(UCommonWidgetCarousel* widgetCarousel, int32 newPageIndex);

	FTimerHandle TimerHandle_Animation;

	struct FAttackResults* ResultsData;

	UFUNCTION()
	void Attack(int32 attackingAmount);

	UFUNCTION()
	void UpdateUI(bool regionCaptured);

	int32 CurrentAttacking();

	UFUNCTION()
	void StartNumberAnimation();

	UFUNCTION()
	void ContinueNumberAnimation();

	void ExecuteAttack();

	UFUNCTION()
	void LeftCarouselAction();

	void LeftCarouselCheck();

	UFUNCTION()
	void RightCarouselAction();

	void RightCarouselCheck();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	bool VisualRandomize = false;

	float DisplayTimeDelay = 0.0f;

	bool AttackInProgress = false;

protected:
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* FailedSound;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* SuccessSound;

public:

	UFUNCTION()
	void ClosePopup();

	void ShowPopup(ARegion* attackingRegion, int32 enemyCount, FColor enemyColor);

	virtual void  NativeConstruct();

	class APlayerCharacter* Player;

};
