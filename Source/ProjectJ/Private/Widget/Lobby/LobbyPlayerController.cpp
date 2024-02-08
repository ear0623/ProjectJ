// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/LobbyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Widget/Lobby/ChatUserWidget.h"
#include "Widget/Lobby/LobbyWidget.h"
#include "Widget/Lobby/LobbyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ClientComponent.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	ClientComponent = CreateDefaultSubobject<UClientComponent>(TEXT("ClientCompo"));

}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem && DefaultIMC)
		SubSystem->AddMappingContext(DefaultIMC, 0);


	check(HUdWidgetClass);
	if (HUdWidgetClass != nullptr)
	{
		HUdwidget = CreateWidget<ULobbyWidget>(GetWorld(), HUdWidgetClass); 
		HUdwidget->AddToViewport();
	}

	ClientComponent->Connect();
}

bool ALobbyPlayerController::C2S_SendMessage_Validate(const FString& InMessage)
{
	return true;
}

void ALobbyPlayerController::C2S_SendMessage_Implementation(const FString& InMessage)
{
	TObjectPtr<ALobbyGameModeBase> LobbyGameMode = Cast<ALobbyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (LobbyGameMode)
	{
		uint32 InMessageLength = InMessage.Len();
		SendClientToServer(InMessageLength,InMessage);
	}
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		//for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ALobbyPlayerController* LobbyPC = Cast<ALobbyPlayerController>(*It);
		if (LobbyPC)
		{
			LobbyPC->S2C_SendMessage(InMessage);
		}
	}

}

void ALobbyPlayerController::S2C_SendMessage_Implementation(const FString& InMessage)
{
	TObjectPtr<ALobbyGameModeBase> LobbyGameMode = Cast<ALobbyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (LobbyGameMode)
	{
		RecvServerToClient();
	}
	if (HUdwidget)
	{
		HUdwidget->ChatWidget->AddMessage(InMessage);

	}
	
}


void ALobbyPlayerController::SendClientToServer(uint32 Type, const FString& Text)
{
	ClientComponent->Send(Type, Text);
	int32 Value = 1024;
	uint8 Buffer = static_cast<uint8>(Value);
	int32 BufferSize = sizeof(Buffer);
	//	ClientComponent->Receive(ClientComponent->GetSocket(),&Buffer,BufferSize);
}

void ALobbyPlayerController::RecvServerToClient()
{
	//ClientComponent->Recv();
	/*int32 Value = 1024;
	uint8 Buffer = static_cast<uint8>(Value,0,255);
	int32 BufferSize = sizeof(Buffer);
	ClientComponent->Receive(ClientComponent->GetSocket(),&Buffer,BufferSize);*/
}