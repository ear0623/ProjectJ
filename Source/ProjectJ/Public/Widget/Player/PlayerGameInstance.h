// Fill out your   copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "PlayerGameInstance.generated.h"


class FSocket;
class ISocketSubsystem;
/**
 * 
 */
UCLASS()
class PROJECTJ_API UPlayerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPlayerGameInstance();

	virtual void Init();

	FSocket* Socket;
	ISocketSubsystem* SocketSubsystem;

	void OpenWorld();
};
