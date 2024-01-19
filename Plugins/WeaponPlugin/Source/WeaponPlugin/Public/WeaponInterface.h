// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"



UINTERFACE(Blueprintable)
class WEAPONPLUGIN_API UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class WEAPONPLUGIN_API IWeaponInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void WeaponShoot();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SettingOwner(ACharacter *character);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClearOwner();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EquipWeapon();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DropWeapon();

};