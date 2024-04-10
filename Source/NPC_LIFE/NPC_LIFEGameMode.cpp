// Copyright Epic Games, Inc. All Rights Reserved.

#include "NPC_LIFEGameMode.h"
#include "NPC_LIFECharacter.h"
#include "UObject/ConstructorHelpers.h"

ANPC_LIFEGameMode::ANPC_LIFEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
