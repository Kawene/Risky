// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GamePhase.h"
#include "TurnManager.generated.h"

class ABaseCharacter;

UCLASS()
class RISKY_API ATurnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnManager();
	
	void Initialize(TArray<ABaseCharacter*>* allPlayers);

	UFUNCTION(BlueprintCallable)
	void StartTurn();

	UFUNCTION()
	void ProceedToNextPhase();

	void CharacterDied(ABaseCharacter* corpse);

private:	

	UPROPERTY()
	TArray<ABaseCharacter*> Characters;

	int32 CurrentCharracterIndex;

	UPROPERTY()
	EGamePhase CurrentPhase;

	UFUNCTION()
	void EndTurn();

	UFUNCTION()
	int32 GetsNumberOfUnitsToDeploy(ABaseCharacter* character);

};
