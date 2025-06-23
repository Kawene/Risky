// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MusicManager.generated.h"

/**
 * 
 */
UCLASS()
class RISKY_API AMusicManager : public AActor
{
	GENERATED_BODY()


	UFUNCTION()
	void OnMusicFinished();

	UPROPERTY(Transient)
	UAudioComponent* MusicComponent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TArray<USoundBase*> MusicTracks;

	void StartMusicLoop();

	void PlayRandomTrack();

	virtual void BeginPlay() override;

};
