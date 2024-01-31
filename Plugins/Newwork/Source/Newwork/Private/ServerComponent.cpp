// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerComponent.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "HAL/RunnableThread.h"

// Sets default values for this component's properties
UServerComponent::UServerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
}


// Called when the game starts
void UServerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UServerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UServerComponent::StartServer(int32 Port)
{
	if (!SocketSubsystem)
	{
		//socket test
		return false;
	}
	FIPv4Endpoint Endpoint(FIPv4Address::Any, Port);
	TSharedPtr<FInternetAddr>Addr = Endpoint.ToInternetAddr();
	if (!Addr.IsValid())
	{
		//Addr
		return false;
	}
	FSocket* ListenSocket = FTcpSocketBuilder(TEXT("ServerSocket")).BoundToEndpoint(Endpoint).Listening(10);
	if (!ListenSocket)
	{
		//listensocket
		return false;
	}
	//FRunnableThread::Create(new FServerThread())
}

void UServerComponent::HandleClientCommunication(FSocket* ClientSocket)
{
}

