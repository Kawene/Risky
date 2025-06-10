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

	UFUNCTION()
	void ButtonAction();


protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USlider* SliderUnits;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* ActionButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* CloseButton;

	UUserWidget* ParentWidget;

	void ShowPopup(int32 MaxValue, FString textButton);

	virtual void  NativeConstruct();

	UFUNCTION()
	void ClosePopup();

	class APlayerCharacter* Player;
	
};
