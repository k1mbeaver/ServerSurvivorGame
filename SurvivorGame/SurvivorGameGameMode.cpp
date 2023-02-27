// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurvivorGameGameMode.h"
#include "SurvivorGameHUD.h"
#include "SurvivorGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASurvivorGameGameMode::ASurvivorGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASurvivorGameHUD::StaticClass();
}
