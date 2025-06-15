// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ui/DefeatUI.h"
#include "PauseUI.generated.h"


UCLASS()
class RISKY_API UPauseUI : public UDefeatUI
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBaseButton* OptionButton;

	UFUNCTION()
	void OpenOptions();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UOptionsUI* OptionDialog;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UVerticalBox* PauseContainer;

public:
	virtual void  NativeConstruct();
};
