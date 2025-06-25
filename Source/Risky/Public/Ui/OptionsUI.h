// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsUI.generated.h"

UCLASS()
class RISKY_API UOptionsUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* SFXText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USlider* SFXSlider;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* MusicText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USlider* MusicSlider;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* ApplyButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UComboBoxString* PhasesStepsChoice;

	class USettingsSaved* Settings;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundMix* SoundMix;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundClass* SFXSoundClass;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundClass* MusicSoundClass;

	UFUNCTION()
	void ApplyAndSaveSettings();

	UFUNCTION()
	void ApplySettings();

	UFUNCTION()
	void SaveSettings();

	UFUNCTION()
	void UpdateSFXText(float value);

	UFUNCTION()
	void UpdateMusicText(float value);

	UFUNCTION()
	void BackAction();

	virtual void  NativeConstruct();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options", meta = (ExposeOnSpawn = "true"))
	class UWidget* Parent;
};
