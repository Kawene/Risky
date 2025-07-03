// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInformationUI.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInformationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnitsAmountOwned = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RegionAmountOwned = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DeploymentAmount = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDead = false;

	FPlayerInformationData();

	FPlayerInformationData(class ATurnManager* turnManager, class ABaseCharacter* character);
};

UCLASS()
class RISKY_API UPlayerInformationUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* PlayerColor;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* UnitsAmountOwned;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* RegionAmountOwned;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* DeploymentAmount;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* DeathSign;

	bool PlayerDead = false;

public:

	void InitializeData(FColor color, FPlayerInformationData* playerInformation);

	void UpdateInformation(FPlayerInformationData* playerInformation);

	void PlayerDied();

	bool IsPlayerDead() const { return PlayerDead; }

};
