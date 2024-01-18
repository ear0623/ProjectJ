// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDele_UppateTrigger);


UINTERFACE(Blueprintable)
class WEAPONPLUGIN_API UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class WEAPONPLUGIN_API IWeaponInterface
{
	GENERATED_BODY()

public:
	
	virtual void WeaponShoot()=0;

	//UFUNCTION(BlueprintAssignable)
	FDele_UppateTrigger UpdateTrigger;

};