// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Testing_GroundsGameMode.h"
#include "Testing_GroundsHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATesting_GroundsGameMode::ATesting_GroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behaviour/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATesting_GroundsHUD::StaticClass();
}
