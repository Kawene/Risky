// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnManager.generated.h"

class ABaseCharacter;

UENUM(BlueprintType)
enum class EGamePhase : uint8 {
	DeploymentPhase, 
	AttackPhase,
	FortificationPhase
};

UCLASS()
class RISKY_API ATurnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnManager();

	UFUNCTION(BlueprintCallable)
	void StartTurn();

	UFUNCTION()
	void ProceedToNextPhase();

	UFUNCTION()
	void EndTurn();

	virtual void Tick(float DeltaTime) override;



private:	

	UPROPERTY()
	TArray<ABaseCharacter*> Characters;

	int32 CurrentCharracterIndex;

	UPROPERTY()
	EGamePhase CurrentPhase;

	void GatherCharacters();


protected:
	virtual void BeginPlay() override;

};
