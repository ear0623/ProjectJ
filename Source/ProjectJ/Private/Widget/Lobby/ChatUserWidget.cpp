// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/ChatUserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Widget/Lobby/LobbyPlayerController.h"


void UChatUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCountTextBox = Cast<UTextBlock>(GetWidgetFromName("PlayerCountTextBox"));
	ChatScrollBox = Cast<UScrollBox>(GetWidgetFromName("ChatScrollBox"));
	ChatInputTextBox = Cast<UEditableTextBox>(GetWidgetFromName("ChatInputTextBox"));
	if (ChatInputTextBox)
	{
		ChatInputTextBox->OnTextChanged.AddDynamic(this, &UChatUserWidget::ProcessChanged);
		ChatInputTextBox->OnTextCommitted.AddDynamic(this, &UChatUserWidget::ProcessCommitted);
	}
}

void UChatUserWidget::UpatePlayerCount(int32 InPlayerCount)
{
	if (PlayerCountTextBox) 
	{
		//FString Message = FString::Printf(TEXT("%d Έν"), InPlayerCount); 
		//PlayerCountTextBox->SetText(FText::FromString(Message)); 
	}
}

void UChatUserWidget::ProcessChanged(const FText& Text)
{

}

void UChatUserWidget::ProcessCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	ALobbyPlayerController* LobbyPC = Cast<ALobbyPlayerController>(GetOwningPlayer());
	
	if (LobbyPC)
	{
		switch (CommitMethod)
		{
		case ETextCommit::OnEnter:
			LobbyPC->C2S_SendMessage(ChatInputTextBox->GetText().ToString());
			LobbyPC->SendClientToServer(ChatInputTextBox->GetText().ToString());
			ChatInputTextBox->SetText(FText::FromString(TEXT("")));
			break;
		case ETextCommit::OnCleared:
			ChatInputTextBox->SetUserFocus(LobbyPC);
			break;
		}
	}
}

void UChatUserWidget::AddMessage(const FString& InMessge)
{
	UE_LOG(LogTemp, Warning, TEXT("ChastScrollBoxos True"));
	if (ChatScrollBox)
	{
		
		UTextBlock* NewMessage = NewObject<UTextBlock>(ChatScrollBox);
		if (NewMessage)
		{
			NewMessage->SetText(FText::FromString(InMessge));
			FSlateFontInfo NewFont = NewMessage->GetFont();
			NewFont.Size = 18;
			NewMessage->SetFont(NewFont);
			ChatScrollBox->AddChild(NewMessage);
			ChatScrollBox->ScrollToEnd();
		}
	}
}

