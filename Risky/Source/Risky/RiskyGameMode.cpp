// Copyright Epic Games, Inc. All Rights Reserved.

#include "RiskyGameMode.h"
#include "RiskyPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ARiskyGameMode::ARiskyGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARiskyPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Test"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}