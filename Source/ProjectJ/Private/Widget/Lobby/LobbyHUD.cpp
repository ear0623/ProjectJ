// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/LobbyHUD.h"
#include "Blueprint/UserWidget.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	//check(HUdWidgetClass);
	if (HUdWidgetClass != nullptr)
	{
		HUdwidget = CreateWidget<UUserWidget>(GetWorld(), HUdWidgetClass); 
		HUdwidget->AddToViewport(); 
	} 


}
