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

	double TotalAiTimes;

	UPROPERTY(EditAnywhere)
	EAiPhasesSteps AiPhasesSteps;

	TArray<class AProvince*> Provinces;

	UPROPERTY()
	TArray<ABaseCharacter*> Characters;

	UFUNCTION()
	int32 GetsNumberOfUnitsToDeploy(ABaseCharacter* character);

	TArray<ABaseCharacter*> GetTurnOrderFrom(ABaseCharacter* character);

	bool InSimulation;
		 
private:	

	int32 CurrentCharacterIndex;

	UPROPERTY()
	EGamePhase CurrentPhase;

	UFUNCTION()
	void EndTurn();

	void WriteTotalTime();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UTurnTrackerUI> TurnTrackerUIClass;

	UPROPERTY()
	class UTurnTrackerUI* TurnTrackerUI;

};
