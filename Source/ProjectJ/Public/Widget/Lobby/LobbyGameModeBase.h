// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameModeBase.generated.h"


class UClientComponent;
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

	UPROPERTY()
	TObjectPtr<UClientComponent> ClientComponent;

	UFUNCTION()
	void SendClientToServer(uint32 Type, const FString& Text);

	void RecvServerToClient(FSocket* Socket, uint8* Results, int32 Size);

	//virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)override;

};
