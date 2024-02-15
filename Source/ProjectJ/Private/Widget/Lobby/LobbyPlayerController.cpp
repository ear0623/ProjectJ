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
}

bool ALobbyPlayerController::C2S_SendMessage_Validate(const FString& InMessage)
{
	return true;
}

void ALobbyPlayerController::C2S_SendMessage_Implementation(const FString& InMessage)
{

	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
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


void ALobbyPlayerController::SendClientToServer( const FString& Text)
{
	uint32 InMessageLength = 1024;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SendClientTo ")));
	ClientComponent->Send(InMessageLength, Text);
	int32 Value = 1024;
	uint8 Buffer = static_cast<uint8>(Value);
	int32 BufferSize = sizeof(Buffer);
}

void ALobbyPlayerController::RecvServerToClient()
{
}