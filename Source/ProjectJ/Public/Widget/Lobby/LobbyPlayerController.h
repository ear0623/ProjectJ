// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"


class UInputMappingContext;
class UChatUserWidget;
class ULobbyWidget;

/**
 * 
 */
UCLASS()
class PROJECTJ_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")
	TObjectPtr<UInputMappingContext> DefaultIMC;
	

	virtual void BeginPlay() override;

	/// ///
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<ULobbyWidget> HUdWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	TObjectPtr<ULobbyWidget> HUdwidget;

	/// /// ///
	
	UFUNCTION(Server, Unreliable, WithValidation)
	void C2S_SendMessage(const FString& InMessage); //client call
	bool C2S_SendMessage_Validate(const FString& InMessage);
	void C2S_SendMessage_Implementation(const FString& InMessage); //server execute

	UFUNCTION(Client, Reliable)
	void S2C_SendMessage(const FString& InMessage); //Server Call
	void S2C_SendMessage_Implementation(const FString& InMessage); //client execute
};
