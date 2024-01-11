// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UStaticMeshComponent;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	AMMO UMETA(DisplayName = "Ammo"),
	Magazine UMETA(DisplayName = "Mag"),
	AssaultRifle UMETA(DisplayName= "AR"),
};

UCLASS()
class WEAPON_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(BlueprintReadOnly,EditAnywhere, meta=(AllowPrivateAccess = "true"))
	EWeaponType WeaponType;
};
