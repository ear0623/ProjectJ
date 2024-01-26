// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDele_UpdateHp, float, CurHp, float, MaxHp, float, CurHpText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDele_UpdateSTM, float, CurSTM, float, MaxSTM);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_UpdateMag, int, Mag);

/**
 * 
 */
UCLASS()
class PROJECTJ_API APlayerPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	APlayerPlayerState();

public:

	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void AddDamage(float Damage);

	UFUNCTION()
	void AddSTM(); // 1. ÀÌ °ªÀ»

	UFUNCTION()
	void UseSTM();

	UFUNCTION()
	void AddMag();

	UFUNCTION()
	void UseMag();

public:

	UFUNCTION()
	void OnRep_CurHp();

	UFUNCTION()
	void OnRep_CurHpText();
	

	UFUNCTION()
	void OnRep_CurSTM();

	UFUNCTION()
	void OnRep_Mag();

public:

	UPROPERTY(ReplicatedUsing = OnRep_CurHp)
	float m_CurHp;

	UPROPERTY(ReplicatedUsing = OnRep_CurHpText)
	float m_CurHpText;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateHp m_Dele_UpdateHp;

	//UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	//FDele_UpdateHp m_Dele_UpdateHp;

	UPROPERTY(ReplicatedUsing = OnRep_CurSTM)
	float m_CurSTM;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateSTM m_Dele_UpdateSTM;

	UPROPERTY(ReplicatedUsing = OnRep_Mag)
	float m_Mag;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateMag m_Dele_UpdateMag;

	void UpdateBind();

	FTimerHandle th_UpdateBind;
	
	
};
