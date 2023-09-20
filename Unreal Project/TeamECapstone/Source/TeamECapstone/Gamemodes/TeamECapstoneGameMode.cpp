// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamECapstoneGameMode.h"
#include "TeamECapstoneCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATeamECapstoneGameMode::ATeamECapstoneGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
