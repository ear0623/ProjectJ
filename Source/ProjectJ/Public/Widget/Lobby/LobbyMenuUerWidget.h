// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyMenuUerWidget.generated.h"

class UButton;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class PROJECTJ_API ULobbyMenuUerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ProcessMakeRoom();

	UFUNCTION()
	void ProcessConnectServer();


public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components",meta=(BindWidget))
	TObjectPtr<UButton> MakeRoomButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components", meta = (BindWidget))
	TObjectPtr<UButton> ConnectServerButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components", meta = (BindWidget))
	TObjectPtr<UEditableTextBox> IPTextBox;
};
