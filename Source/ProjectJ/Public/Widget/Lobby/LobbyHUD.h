// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LobbyHUD.generated.h"


class UUserWidget;
/**
 * 
 */
UCLASS()
class PROJECTJ_API ALobbyHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Widget")
	TSubclassOf<UUserWidget> HUdWidgetClass;

	UPROPERTY(BlueprintReadWrite,Category="Widget")
	TObjectPtr<UUserWidget> HUdwidget;
};
