// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponInterface.h"
#include "WeaponBase.generated.h"

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
	UPROPERTY(BlueprintReadOnly,Category = "Variable",meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter> OwnedCharacter;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Variable",meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> TriggerEffect;

public:
	/////////�������̽�///////////////////////////////////////////////////////////////////
	virtual void WeaponShoot()override;

public:
	//MyOverrap
	UFUNCTION()
	void OnWeaponBeingOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Trigger();
};