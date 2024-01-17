// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponInterface.h"
#include "WeaponBase.generated.h"

DECLARE_DELEGATE(FDele_UpdateInteraction);

class UStaticMeshComponent;
class USphereComponent;
class ACharacter;
class UParticleSystem;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	ShotGun UMETA(DisplayName = "SG"),
	AssaultRifle UMETA(DisplayName = "AR"),
};

UCLASS()
class WEAPON_API AWeaponBase : public AActor, public IWeaponInterface
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

	////////Component///////////////////////////////////////////////////////////////////
	//����
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	//����Ÿ��
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;

	//�ݸ���//
	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category= "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereCollision;

	////////Variable/////////////////////////////////////////////////////////////////////
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Variable",meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> TriggerEffect;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Variable", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter> OwnedCharacter;

	//////////////////////////////////��������Ʈ/////////////////////////////////////////////////////////////////////
public:

	//FDele_UpdateShoot UpdateTrigger; 

	FDele_UpdateInteraction UpdateInteraction;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps)const override;


public:
	/////////�������̽�///////////////////////////////////////////////////////////////////
	virtual void WeaponShoot()override;

public:
	/////////����///////////////////////////////////////////////////////////////////
	UFUNCTION(Server, Reliable)
	void EquipWeapon();

	void EquipWeapon_Implementation();

	UFUNCTION(NetMulticast,Reliable)
	void EquipWeapon_Multicast();

	void EquipWeapon_Multicast_Implementation();

	UFUNCTION(Server, Reliable)
	void DropWeapon();

	void DropWeapon_Implementation();

	void Trigger();

public:
};
