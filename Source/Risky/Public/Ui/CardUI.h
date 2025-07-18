// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Manager/CardManager.h"
#include "CardUI.generated.h"


UCLASS()
class RISKY_API UCardUI : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* CardTypeIcon;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* RegionVisual;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* RegionName;

	class ARegion* Region;

	ECardType CardType;


public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	void UpdateColor();

};
