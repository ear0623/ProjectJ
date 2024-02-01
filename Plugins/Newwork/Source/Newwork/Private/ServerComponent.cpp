// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerComponent.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "HAL/RunnableThread.h"

// Sets default values for this component's properties
UServerComponent::UServerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	
}


// Called when the game starts
void UServerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM); 
	ListenSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("Default"), false); 
	ClientSocket = ListenSocket->Accept(TEXT("ClientSocket")); 
}


// Called every frame
void UServerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UServerComponent::MadeSocket()
{


	if (!SocketSubsystem)
	{
		//socket empty
		return;
	}
	if (!ListenSocket)
	{
		//socket error
		return;
	}
	FIPv4Endpoint Endpoint(FIPv4Address::Any, 15689);
	FIPv4Address Addr = Endpoint.Address;

	TSharedRef<FInternetAddr> ListenAddr = SocketSubsystem->CreateInternetAddr();
	ListenAddr->SetIp(Addr.Value);
	ListenAddr->SetPort(Endpoint.Port);

	if (ListenSocket->Bind(*ListenAddr))
	{
		if (ListenSocket->Listen(10))
		{
			//success
		}
		else
		{
			//fail
		}
	}

	if (!ClientSocket)
	{
		//socket error
	}
	else
	{
		//success
		// 클라이언트 소켓이 성공적으로 수락됨
		// 클라이언트와의 통신이 가능한 상태가 됨

	}



	if (ListenSocket)
	{
		ListenSocket->Close();
		ISocketSubsystem::Get()->DestroySocket(ListenSocket);
	}
	if (ClientSocket)
	{
		ClientSocket->Close();
		ISocketSubsystem::Get()->DestroySocket(ClientSocket);
	}
	
}


