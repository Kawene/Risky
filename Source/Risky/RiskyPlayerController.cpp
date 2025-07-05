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

		EnhancedInputComponent->BindAction(EscapeInput, ETriggerEvent::Started, this, &ARiskyPlayerController::EscapeAction);

		EnhancedInputComponent->BindAction(TabInput, ETriggerEvent::Started, this, &ARiskyPlayerController::TabAction);
	}
}

void ARiskyPlayerController::Move(const FInputActionValue& Value)
{

	if (Player->IsCameraControlled())
	{
		return;
	}

	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector InputVector = FVector(MovementVector, 0);

	Player->AddMovementInput(InputVector, speed, false);

}
void ARiskyPlayerController::EscapeAction()
{
	Player->EscapeAction();
}

void ARiskyPlayerController::TabAction()
{
	Player->TabAction();
}


void ARiskyPlayerController::Tick(float DeltaTime)
{
}