// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Player/PlayerPlayerController.h"
#include "Widget/Player/PlayerGameInstance.h"
#include "Widget/Player/PlayerPlayerState.h"
#include "EnhancedInputSubsystems.h"

void APlayerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem && DefaultIMC)
		SubSystem->AddMappingContext(DefaultIMC, 0);
}

void APlayerPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ResClientPossess();
}

void APlayerPlayerController::ResClientPossess_Implementation()
{
	UPlayerGameInstance* pGameInst = Cast<UPlayerGameInstance>(GetGameInstance());
	if (false == IsValid(pGameInst))
		return;

	
}
