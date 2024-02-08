// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UChatUserWidget;
/**
 * 
 */
UCLASS()
class PROJECTJ_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta= (BindWidget))
	TObjectPtr<UChatUserWidget> ChatWidget;
	
};
