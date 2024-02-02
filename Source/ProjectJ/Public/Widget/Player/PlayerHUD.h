// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay();

public:

	void BindMyPlayerState();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyHp(float CurHp, float MaxHp, int CurHpText);
	void OnUpdateMyHp_Implementation(float CurHp, float MaxHp, int CurHpText);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) // STM = Stemina
	void OnUpdateMySTM(float CurSTM, float MaxSTM);
	void OnUpdateMySTM_Implementation(float CurSTM, float MaxSTM);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyAmmo(int Ammo);
	void OnUpdateMyAmmo_Implementation(int Ammo);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyMag(int Mag);
	void OnUpdateMyMag_Implementation(int Mag);

	//public: NameTag 필요 없을 듯?
	//	void BindPlayerState(class AsootingPlayerState* PlayerState);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HudWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* HudWidget;

	FTimerHandle th_BindMyPlayerState;


};
