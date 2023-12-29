// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectJGameMode.h"
#include "ProjectJCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectJGameMode::AProjectJGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
