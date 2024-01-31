// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerComponent.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"

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
	
}


// Called every frame
void UServerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UServerComponent::InitializeSocketSubsystem()
{
	bool bSuccess = false;
	TObjectPtr<ISocketSubsystem> SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (!SocketSubsystem)
	{
		bSuccess = true;
	}
	return bSuccess;
}

void UServerComponent::AcceptThread(FSocket* ListenSocket)
{
	FSocket* ClientSocket = nullptr;
	while (true)
	{
		FIPv4Endpoint ClientEndpoint;
		//if (ListenSocket->HasPendingConnection())
		//{
			ClientSocket = ListenSocket->Accept(*ClientEndpoint.ToString());
			if (ClientSocket != nullptr)
			{

			}
		//}
	}
}

int32 UServerComponent::ServertoClient()
{
	if (!InitializeSocketSubsystem)
	{
		//Socket
		check(InitializeSocketSubsystem);
	}

	FIPv4Endpoint ListenEndpoint(FIPv4Address::Any, 15689);
	TSharedPtr<FInternetAddr> Addr = ListenEndpoint.ToInternetAddr();
	if (!Addr.IsValid())
	{
		//Address
		check(Addr);
	}

	FSocket* ListenSocket = FTcpSocketBuilder(TEXT("ListenSocket")).AsBlocking().BoundToEndpoint(ListenEndpoint).Listening(5);
	if (!ListenSocket)
	{
		//Listen소켓실패
		check(ListenSocket);
	}

	//FRunnableThread::Create(new AcceptThread,ListenSocket);
	while (true)
	{
		//작업수행
		FPlatformProcess::Sleep(0.1);
	}

	ListenSocket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
	
	//FSocketSubsystem::Shutdown();
	return 0;
}

