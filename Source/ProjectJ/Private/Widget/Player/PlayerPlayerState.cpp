// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Player/PlayerPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Widget/Player/PlayerHUD.h"
#include "GameMode/AJ_Character.h"
#include "WeaponBase.h"

APlayerPlayerState::APlayerPlayerState()
{
	m_CurHp = 100;
	m_CurHpText = 0;
	m_CurSTM = 150;
}

void APlayerPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerPlayerState, m_CurHp);
	DOREPLIFETIME(APlayerPlayerState, m_CurHpText);
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

	m_CurHpText = m_CurHpText + Damage;

	OnRep_CurHp();
}

//void APlayerPlayerState::AddDamage_Text(float Damage)
//{
//	//m_CurHpText = m_CurHpText + Damage;
//
//	//OnRep_CurHpText();
//}


void APlayerPlayerState::AddSTM()
{

	//Stamina Up
	float StaminaUp = 2.0f;


	m_CurSTM = FMath::Clamp((m_CurSTM + StaminaUp), 0.0f, 150.0f);
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("STMU"));
	OnRep_CurSTM();
}

void APlayerPlayerState::UseSTM()
{
	//Stamina Dawn
	float StaminaDawn = 4.0f;

	m_CurSTM = FMath::Clamp((m_CurSTM - StaminaDawn), 0.0f, 150.0f);



	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("STMD"));
	OnRep_CurSTM();
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
		m_Dele_UpdateHp.Broadcast(m_CurHp, 100, m_CurHpText);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("%f"), m_CurHpText));
}

//void APlayerPlayerState::OnRep_CurHpText()
//{
//	//if (m_Dele_UpdateHp.IsBound())
//	//	m_Dele_UpdateHp.Broadcast(m_CurHp, 100, m_CurHpText);
//
//	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("m_CurHpText"));
//
//}

void APlayerPlayerState::OnRep_CurSTM()
{
	if (m_Dele_UpdateSTM.IsBound()) // 바인딩 (팔로우)가 되어 있는지 확인
		m_Dele_UpdateSTM.Broadcast(m_CurSTM, 150); // 브로드케스트 -> 전파한다
}

void APlayerPlayerState::OnRep_Mag()
{
	if (m_Dele_UpdateMag.IsBound())
		m_Dele_UpdateMag.Broadcast(m_Mag);
}

void APlayerPlayerState::UpDateAmmoToHUD(int Ammo)
{
	/*AWeaponBase* ABS = Cast<*/

	

	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (pPlayer0)
	{
		APlayerHUD* pHud = Cast<APlayerHUD>(pPlayer0->GetHUD());
		if (pHud)
		{
			AWeaponBase* AmmoCheck = Cast<AWeaponBase>(this);
			if (AmmoCheck)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, FString::Printf(TEXT("Ammochec true")));
			}
			pHud->OnUpdateMyAmmo(Ammo);

		}
	}

}



