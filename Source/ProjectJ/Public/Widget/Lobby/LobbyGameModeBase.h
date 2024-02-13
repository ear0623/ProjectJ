// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameModeBase.generated.h"



/**
 * 
 */
UCLASS()
class PROJECTJ_API ALobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ALobbyGameModeBase();

public:


	virtual void BeginPlay() override;

	//virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)override;

};
