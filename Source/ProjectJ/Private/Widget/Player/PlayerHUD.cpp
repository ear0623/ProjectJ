// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Player/PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Widget/Player/PlayerPlayerState.h"
#include "WeaponBase.h"

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
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (IsValid(pc))
	{
		APlayerPlayerState* ps = Cast<APlayerPlayerState>(pc->PlayerState);
		if (IsValid(ps))
		{
			ps->m_Dele_UpdateHp.AddDynamic(this, &APlayerHUD::OnUpdateMyHp);
			OnUpdateMyHp(ps->m_CurHp, 100, ps->m_CurHpText);

			ps->m_Dele_UpdateSTM.AddDynamic(this, &APlayerHUD::OnUpdateMySTM); // 값을 확인한다. 
			OnUpdateMySTM(ps->m_CurSTM, 150);

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("HUD Bind Success!"));
			
		

			return;

		}
	}

	m_Dele_UpdateMag.AddDynamic(this, &APlayerHUD::OnUpdateMyMag);
	BindMag(m_Mag);


	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(th_BindMyPlayerState, this, &APlayerHUD::BindMyPlayerState, 0.01f, false);
}

void APlayerHUD::OnUpdateMyHp_Implementation(float CurHp, float MaxHp, int CurHpText)
{
}

void APlayerHUD::OnUpdateMySTM_Implementation(float CurSTM, float MaxSTM) // 전파를 받는다
{
}

void APlayerHUD::OnUpdateMyAmmo_Implementation(int Ammo)
{
}

void APlayerHUD::OnUpdateMyMag_Implementation(int32 Mag)
{
}


void APlayerHUD::BindMag(int32 MagValue)
{
	UE_LOG(LogTemp, Warning, TEXT("MagValue: %d"), MagValue);

	OnUpdateMag.Broadcast(MagValue);
}

//void APlayerHUD::OnUpdateMyMag_Implementation(int Mag)
//{
//}
