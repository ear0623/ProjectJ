// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Player/PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Widget/Player/PlayerPlayerState.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	check(HudWidgetClass);

	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(pPlayer0) == false)
		return;

	pPlayer0->SetInputMode(FInputModeGameOnly());
	pPlayer0->bShowMouseCursor = false;

	BindMyPlayerState();
}

void APlayerHUD::BindMyPlayerState()
{
}

void APlayerHUD::OnUpdateMyHp_Implementation(float CurHp, float MaxHp)
{
}

void APlayerHUD::OnUpdateMySTM_Implementation(float CurSTM, float MaxSTM)
{
}

void APlayerHUD::OnUpdateMyAmmo_Implementation(int Ammo)
{
}

void APlayerHUD::OnUpdateMyMag_Implementation(int Mag)
{
}
