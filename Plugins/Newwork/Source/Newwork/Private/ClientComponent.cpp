// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientComponent.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "HAL/RunnableThread.h"

// Sets default values for this component's properties
UClientComponent::UClientComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClientComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClientComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClientComponent::Connect()
{
	ISocketSubsystem* Socketsubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	FSocket* ServerSocket = Socketsubsystem->CreateSocket(NAME_Stream, TEXT("serversocket"), false);
	if (!Socketsubsystem)
	{
		//subsystem
	}
	if (!ServerSocket)
	{
		//socket
	}
	FIPv4Address ServerIP(127,0,0,1);

	TSharedRef<FInternetAddr> ServerAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	ServerAddr->SetIp(ServerIP.Value);
	ServerAddr->SetPort(15689);

	bool Connected = ServerSocket->Connect(*ServerAddr);

	TArray<uint8> SendBuffer;
	FTimespan WaitTime = FTimespan::FromSeconds(1);
	while (bIsRunning)
	{
		if (Connected)
		{
			int32 ByteSend = 0;
			ServerSocket->Send(SendBuffer.GetData(), SendBuffer.Num(),ByteSend);

			int32 ByteRecived = 0;
			if (ServerSocket->Wait(ESocketWaitConditions::WaitForRead, WaitTime))
			{

			}
		}
	}
}

