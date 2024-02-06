// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/LobbyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Widget/Lobby/ChatUserWidget.h"
#include "Widget/Lobby/LobbyWidget.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem && DefaultIMC)
		SubSystem->AddMappingContext(DefaultIMC, 0);


	FSoftClassPath ChatWidgetObject(TEXT("C:/Work/ProjectJ/Content/ProjectJ/Widget/Lobby/WBP_LobbyWidget.uasset"));
	UClass* WidgetClass = ChatWidgetObject.TryLoadClass<UChatUserWidget>();

	LobbyWidgetObject = Cast<UChatUserWidget>(WidgetClass);
	if (WidgetClass && IsLocalPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("If true"));
		LobbyWidgetObject = CreateWidget<UChatUserWidget>(this, WidgetClass);
		if (LobbyWidgetObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("Lobbywidgettrue"));
			LobbyWidgetObject->AddToViewport();
			//LobbyWidgetObject->RemoveFromViewport();
		}
	}

	
}

bool ALobbyPlayerController::C2S_SendMessage_Validate(const FString& InMessage)
{
	return true;
}

void ALobbyPlayerController::C2S_SendMessage_Implementation(const FString& InMessage)
{
	
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
	
	if (LobbyWidgetObject != nullptr)
	{
		LobbyWidgetObject->AddMessage(InMessage);
	}
	UE_LOG(LogTemp, Warning, TEXT("LobbyWidgetObject Null"));
}
