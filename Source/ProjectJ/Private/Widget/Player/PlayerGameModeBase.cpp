// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Player/PlayerGameModeBase.h"
#include "Widget/Player/PlayerPlayerState.h"

void APlayerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (pPlayer0)
	{
		APlayerPlayerState* pPlayerState = Cast<APlayerPlayerState>(pPlayer0->PlayerState);
		if (pPlayerState)
		{
			pPlayerState->IPS();
		}
	}
}
