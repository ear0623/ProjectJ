// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/LobbyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Widget/Lobby/ChatUserWidget.h"
#include "Widget/Lobby/LobbyWidget.h"
#include "Widget/Lobby/LobbyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

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
	TObjectPtr<ALobbyGameModeBase> LobbyGameMode = Cast<ALobbyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (LobbyGameMode)
	{
		uint32 InMessageLength = InMessage.Len();
		LobbyGameMode->SendClientToServer(InMessageLength,InMessage);
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
	
	if (HUdwidget)
	{
		HUdwidget->ChatWidget->AddMessage(InMessage);
		UE_LOG(LogTemp, Warning, TEXT("true"));
	}
	
}
