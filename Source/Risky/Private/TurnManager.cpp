// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "BaseCharacter.h"

ATurnManager::ATurnManager()
{
	CurrentCharracterIndex = 0;
	PrimaryActorTick.bCanEverTick = true;
	CurrentPhase = EGamePhase::DeploymentPhase;
}

void ATurnManager::BeginPlay()
{
	Super::BeginPlay();


	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurnManager::GatherCharacters, 0.5f, false);
}

void ATurnManager::GatherCharacters()
{
	TArray<AActor*> temp = TArray<AActor*>();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), temp);

	for (AActor* act : temp)
	{
		auto baseCharacter = StaticCast<ABaseCharacter*>(act);
		baseCharacter->TurnManagerRef(this);
		Characters.Push(StaticCast<ABaseCharacter*>(act));

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Found One"));
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Im alive"));
}

void ATurnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurnManager::StartTurn()
{
	CurrentPhase = EGamePhase::DeploymentPhase;
	Characters[CurrentCharracterIndex]->StartDeploymentPhase();
}

void ATurnManager::ProceedToNextPhase()
{
	switch (CurrentPhase)
	{
	case EGamePhase::DeploymentPhase:
		CurrentPhase = EGamePhase::AttackPhase;
		Characters[CurrentCharracterIndex]->StartAttackPhase();
		break;
	case EGamePhase::AttackPhase:
		CurrentPhase = EGamePhase::FortificationPhase;
		Characters[CurrentCharracterIndex]->StartFortificationPhase();
		break;
	case EGamePhase::FortificationPhase:
		EndTurn();
		break;
	default:
		break;
	}
}

void ATurnManager::EndTurn()
{
	CurrentCharracterIndex = (CurrentCharracterIndex + 1) % Characters.Num();
	//StartTurn();
}


