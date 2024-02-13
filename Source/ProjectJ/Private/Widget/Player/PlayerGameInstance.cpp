// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Player/PlayerGameInstance.h"
#include "Sockets.h"
#include "Kismet/GameplayStatics.h"


UPlayerGameInstance::UPlayerGameInstance()
{
}

void UPlayerGameInstance::Init()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"),TEXT("Client Socket"));

	FString Address = TEXT("127.0.0.1");
	FIPv4Address IP;
	FIPv4Address::Parse(Address, IP);

	int32 Port = 15689;

	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	Addr->SetIp(IP.Value);
	Addr->SetPort(Port);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Try to Connet")));

	bool isConnected = Socket->Connect(*Addr);

}

void UPlayerGameInstance::OpenWorld()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("DemoBase"), true, TEXT("listen"));
}
