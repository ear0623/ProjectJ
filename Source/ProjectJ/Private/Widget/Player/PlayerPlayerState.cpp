// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Player/PlayerPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Widget/Player/PlayerHUD.h"

APlayerPlayerState::APlayerPlayerState():m_CurHp(100), m_CurSTM(150)
{
}

void APlayerPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerPlayerState, m_CurHp);
	DOREPLIFETIME(APlayerPlayerState, m_CurSTM);
	DOREPLIFETIME(APlayerPlayerState, m_Mag);

}

void APlayerPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UpdateBind();
}

void APlayerPlayerState::UpdateBind()
{
	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (pPlayer0)
	{
		APlayerHUD* pHud = Cast<APlayerHUD>(pPlayer0->GetHUD());
		if (pHud)
		{
			return;

		}
	}

	FTimerManager& TimeMgr = GetWorldTimerManager();
	TimeMgr.SetTimer(th_UpdateBind, this, &APlayerPlayerState::UpdateBind, 0.01f, false);
}

void APlayerPlayerState::AddDamage(float Damage)
{
	m_CurHp = m_CurHp - Damage;

	OnRep_CurHp();
}

void APlayerPlayerState::AddSTM(float P_Run)
{
	m_CurSTM = m_CurSTM - P_Run;

	OnRep_CurSTM();
}

void APlayerPlayerState::UseSTM()
{
}

void APlayerPlayerState::AddMag()
{
	m_Mag = m_Mag + 1;

	OnRep_Mag();
}

void APlayerPlayerState::UseMag()
{
}

void APlayerPlayerState::OnRep_CurHp()
{
	if (m_Dele_UpdateHp.IsBound())
		m_Dele_UpdateHp.Broadcast(m_CurHp, 100);
}

void APlayerPlayerState::OnRep_CurSTM()
{
	if (m_Dele_UpdateSTM.IsBound())
		m_Dele_UpdateSTM.Broadcast(m_CurSTM, 150);
}

void APlayerPlayerState::OnRep_Mag()
{
	if (m_Dele_UpdateMag.IsBound())
		m_Dele_UpdateMag.Broadcast(m_Mag);
}


