// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/OptionsUI.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Ui/BaseButton.h"
#include "SettingsSaved.h"
#include <Kismet/GameplayStatics.h>


void UOptionsUI::NativeConstruct()
{
	Super::NativeConstruct();

	const FString saveSlotName = TEXT("SettingsSaveSlot");
	const int32 userIndex = 0;

	SFXSlider->OnValueChanged.AddDynamic(this, &UOptionsUI::UpdateSFXText);
	MusicSlider->OnValueChanged.AddDynamic(this, &UOptionsUI::UpdateMusicText);
	ApplyButton->Button->OnClicked.AddDynamic(this, &UOptionsUI::ApplySettings);
	ApplyButton->SetButtonText("Apply");
	BackButton->OnClicked.AddDynamic(this, &UOptionsUI::BackAction);

	if (UGameplayStatics::DoesSaveGameExist(saveSlotName, userIndex))
	{
		Settings = Cast<USettingsSaved>(UGameplayStatics::LoadGameFromSlot(saveSlotName, userIndex));
	}
	else
	{
		Settings = Cast<USettingsSaved>(UGameplayStatics::CreateSaveGameObject(USettingsSaved::StaticClass()));
	}

	if (Settings)
	{
		SFXSlider->SetValue(Settings->GetSFXVolume());
		MusicSlider->SetValue(Settings->GetMusicVolume());
		UpdateSFXText(Settings->GetSFXVolume());
		UpdateMusicText(Settings->GetMusicVolume());
	}
}

void UOptionsUI::ApplySettings()
{
	Settings->SetSFXVolume(SFXSlider->GetValue());
	Settings->SetMusicVolume(MusicSlider->GetValue());
	Settings->SaveSettings();

	if (SoundMix && SFXSoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(
			GetWorld(), SoundMix, SFXSoundClass, Settings->GetSFXVolume(), 1.0f, 0.0f, true
		);
	}

	if (SoundMix && MusicSoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(
			GetWorld(), SoundMix, MusicSoundClass, Settings->GetMusicVolume(), 1.0f, 0.0f, true
		);
	}

	if (SoundMix)
	{
		UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
	}


	BackAction();
}

void UOptionsUI::UpdateSFXText(float value)
{
	SFXText->SetText(FText::AsNumber(FMath::RoundToInt(value * 100)));
}

void UOptionsUI::UpdateMusicText(float value)
{
	MusicText->SetText(FText::AsNumber(FMath::RoundToInt(value * 100)));
}

void UOptionsUI::BackAction()
{
	if (Parent)
	{
		Parent->SetVisibility(ESlateVisibility::Visible);

	}

	this->SetVisibility(ESlateVisibility::Hidden);
	this->SetVisibility(ESlateVisibility::Collapsed);
}

