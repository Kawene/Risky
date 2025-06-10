// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseButton.generated.h"


UCLASS()
class RISKY_API UBaseButton : public UUserWidget
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ButtonText;

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	class UButton* Button;

	UFUNCTION(BlueprintCallable)
	void SetButtonText(const FString& text);
};
