// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamECapstoneGameMode.h"
#include "TeamECapstoneCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATeamECapstoneGameMode::ATeamECapstoneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
