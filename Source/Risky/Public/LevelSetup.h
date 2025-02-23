// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelSetup.generated.h"

class ACharacterBase;

UCLASS()
class RISKY_API ALevelSetup : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int NumberOfAI;

	void InitializeLevel();

public:
	ALevelSetup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
