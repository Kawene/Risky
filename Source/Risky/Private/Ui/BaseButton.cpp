// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UBaseButton::SetButtonText(const FString& text)
{	
	ButtonText->SetText(FText::FromString(text));
}

