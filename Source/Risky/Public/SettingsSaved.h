// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSaved.generated.h"

/**
 * 
 */
UCLASS()
class RISKY_API USettingsSaved : public USaveGame
{
	GENERATED_BODY()

	UPROPERTY()
	float SFXVolume = 1.0f;

	UPROPERTY()
	float MusicVolume = 1.0f;


public:
	void SetSFXVolume(float value);

	void SetMusicVolume(float value);

	float GetSFXVolume() const;

	float GetMusicVolume() const;

	void SaveSettings();
	
};
