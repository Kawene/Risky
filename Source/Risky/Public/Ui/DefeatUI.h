// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ui/VictoryUI.h"
#include "DefeatUI.generated.h"

UCLASS()
class RISKY_API UDefeatUI : public UVictoryUI
{
	GENERATED_BODY()
protected:
	

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* ResumeButton;

	UFUNCTION()
	void ResumeGame();

public:
	virtual void  NativeConstruct();

	class UMainUI* MainUIReference;
};
