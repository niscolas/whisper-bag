// Copyright Epic Games, Inc. All Rights Reserved.

#include "WhisperBagGameMode.h"
#include "WhisperBagCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWhisperBagGameMode::AWhisperBagGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
