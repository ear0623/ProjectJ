// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Lobby/LobbyMenuUerWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/Player/PlayerGameInstance.h"

void ULobbyMenuUerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MakeRoomButton = Cast<UButton>(GetWidgetFromName(TEXT("MakeRoomButton")));
	ConnectServerButton = Cast<UButton>(GetWidgetFromName(TEXT("ConnectServerButton")));
	IPTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IPTextBox")));

	if (MakeRoomButton)
	{
		MakeRoomButton->OnClicked.AddDynamic(this, &ULobbyMenuUerWidget::ProcessMakeRoom);
	}

	if (ConnectServerButton)
	{
		ConnectServerButton->OnClicked.AddDynamic(this, &ULobbyMenuUerWidget::ProcessConnectServer);
	}
}

void ULobbyMenuUerWidget::ProcessMakeRoom()
{
	TObjectPtr<UPlayerGameInstance> GameInstance= Cast< UPlayerGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OpenWorld();
	}
	//UGameplayStatics::OpenLevel(GetWorld(), TEXT("DemoBase"), true, TEXT("listen"));
}

void ULobbyMenuUerWidget::ProcessConnectServer()
{
	if (IPTextBox)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*IPTextBox->GetText().ToString()));
	}
}
