// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/LobbyPlayerController.h"
#include "EnhancedInputSubsystems.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem && DefaultIMC)
		SubSystem->AddMappingContext(DefaultIMC, 0);
}
