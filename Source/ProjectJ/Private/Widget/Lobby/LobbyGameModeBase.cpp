// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/LobbyGameModeBase.h"
#include "ClientComponent.h"

ALobbyGameModeBase::ALobbyGameModeBase()
{
	ClientComponent = CreateDefaultSubobject<UClientComponent>(TEXT("ClientCompo"));
	
}

void ALobbyGameModeBase::BeginPlay()
{
	ClientComponent->TestConnect();
	
}

void ALobbyGameModeBase::SendClientToServer(uint32 Type, const FString& Text)
{
	ClientComponent->Send(Type, Text);
	int32 Value = 1024;
	uint8 Buffer = static_cast<uint8>(Value);
	int32 BufferSize = sizeof(Buffer);
	ClientComponent->Receive(ClientComponent->GetSocket(),&Buffer,BufferSize);
}

void ALobbyGameModeBase::RecvServerToClient()
{
	//ClientComponent->Recv();
	/*int32 Value = 1024;
	uint8 Buffer = static_cast<uint8>(Value,0,255);
	int32 BufferSize = sizeof(Buffer);
	ClientComponent->Receive(ClientComponent->GetSocket(),&Buffer,BufferSize);*/
}
