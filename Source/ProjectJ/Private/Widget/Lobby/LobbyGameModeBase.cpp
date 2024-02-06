// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/LobbyGameModeBase.h"
#include "ClientComponent.h"

ALobbyGameModeBase::ALobbyGameModeBase()
{
	ClientComponent = CreateDefaultSubobject<UClientComponent>(TEXT("ClientCompo"));
	
}

void ALobbyGameModeBase::BeginPlay()
{

}

void ALobbyGameModeBase::SendClientToServer(uint32 Type, const FString& Text)
{
	ClientComponent->Send(Type, Text);
}

void ALobbyGameModeBase::RecvServerToClient(FSocket* Socket, uint8* Results, int32 Size)
{

}
