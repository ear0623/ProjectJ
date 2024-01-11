// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	AMMO UMETA(DisplayName = "Ammo"),
	Magazine UMETA(DisplayName = "Mag"),
	AssaultRifle UMETA(DisplayName = "AR"),
};

UINTERFACE(Blueprintable)
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class WEAPON_API IWeaponInterface
{
	GENERATED_BODY()

public:
	
	virtual void WeaponShoot()=0;
};