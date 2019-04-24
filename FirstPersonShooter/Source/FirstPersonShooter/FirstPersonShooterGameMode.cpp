// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FirstPersonShooterGameMode.h"
#include "FirstPersonShooterHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFirstPersonShooterGameMode::AFirstPersonShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behaviors/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFirstPersonShooterHUD::StaticClass();
}
