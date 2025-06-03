// Copyright Epic Games, Inc. All Rights Reserved.

#include "RiskyPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Character/PlayerCharacter.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ARiskyPlayerController::ARiskyPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableClickEvents = true;
}

void ARiskyPlayerController::BeginPlay()
{ 
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	Player = Cast<APlayerCharacter>(GetPawn());
}

void ARiskyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MovementInput, ETriggerEvent::Triggered, this, &ARiskyPlayerController::Move);

	}
}

void ARiskyPlayerController::Move(const FInputActionValue& Value)
{

	if (Player->IsCameraMoving())
	{
		return;
	}

	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector InputVector = FVector(MovementVector, 0);

	Player->AddMovementInput(InputVector, speed, false);

}
void ARiskyPlayerController::Tick(float DeltaTime)
{
}