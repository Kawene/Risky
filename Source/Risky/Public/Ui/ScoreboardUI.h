// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreboardUI.generated.h"

/**
 * 
 */
UCLASS()
class RISKY_API UScoreboardUI : public UUserWidget
{
	GENERATED_BODY()
	



	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerInformationUI> PlayerInformationClass;

	bool isInitialized = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* ScoreboardGrid;

public:

	void ShowScoreboard();

	void InitializeGrid();

	void UpdateGridInformation();

};
