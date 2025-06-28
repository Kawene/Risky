// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsSaved.h"
#include <Kismet/GameplayStatics.h>

void USettingsSaved::SetSFXVolume(float value)
{
	SFXVolume = value;
}

void USettingsSaved::SetMusicVolume(float value)
{
	MusicVolume = value;
}

float USettingsSaved::GetSFXVolume() const
{
	return SFXVolume;
}

float USettingsSaved::GetMusicVolume() const
{
	return MusicVolume;
}

EAiPhasesSteps USettingsSaved::GetPhasesSteps() const
{
	return PhasesSteps;
}

void USettingsSaved::SetPhasesSteps(EAiPhasesSteps phase)
{
	PhasesSteps = phase;
}

void USettingsSaved::SaveSettings()
{
	FString saveSlotName = TEXT("SettingsSaveSlot");
	UGameplayStatics::SaveGameToSlot(this, saveSlotName, 0);
}
