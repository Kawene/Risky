// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitsDialogUI.generated.h"

/**
 * 
 */
UCLASS()
class RISKY_API UUnitsDialogUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* SliderText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ActionButtonText;

	UFUNCTION()
	void ButtonAction();

	UFUNCTION()
	void ClosePopup();

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USlider* SliderUnits;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ActionButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CloseButtonText;

	UUserWidget* ParentWidget;

	void ShowPopup(int32 MaxValue, FText textButton);

	virtual void  NativeConstruct();

	class APlayerCharacter* Player;
	
};
