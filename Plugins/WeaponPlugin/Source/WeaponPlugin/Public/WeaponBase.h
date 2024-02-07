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
class UMagZineComponent;
class AAmmoBase;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	ShotGun UMETA(DisplayName = "SG"),
	AssaultRifle UMETA(DisplayName = "AR"),
};

UCLASS()
class WEAPONPLUGIN_API AWeaponBase : public AActor, public IWeaponInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	////////Component///////////////////////////////////////////////////////////////////
	//외형
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	//무기타입
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;

	//콜리전//
	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category= "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereCollision;

	////////Variable/////////////////////////////////////////////////////////////////////
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Variable",meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> TriggerEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMagZineComponent> MagzineCompo;
public:
	UPROPERTY(BlueprintReadOnly, Category = "Variable")
	TObjectPtr<ACharacter> OwnedCharacter;
public:
	/////////인터페이스///////////////////////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void WeaponShoot();

	void WeaponShoot_Implementation();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SettingOwner(ACharacter *character);

	void SettingOwner_Implementation(ACharacter *character);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClearOwner();

	void ClearOwner_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EquipWeapon();

	void EquipWeapon_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DropWeapon();

	void DropWeapon_Implementation();

public:

	UFUNCTION(Server, Reliable)
	void EquipWeapon_Server();

	void EquipWeapon_Server_Implementation();

	UFUNCTION(NetMulticast,Reliable)
	void EquipWeapon_Multicast();

	void EquipWeapon_Multicast_Implementation();

	/*UFUNCTION(Server, Reliable)
	void DropWeapon();

	void DropWeapon_Implementation();*/

	//UFUNCTION(Server, Reliable)
	//void DropWeapon_Multicast();
	UFUNCTION(NetMulticast, Reliable)
	void DropWeapon_Multicast();

	void DropWeapon_Multicast_Implementation();

	UFUNCTION()
	void Trigger();
	//chracter-trigger- winterface- weapon
public:
	FName WeaponTag;

	FName GetWeaponTag()const { return WeaponTag; }

	void SetWeaponTag(const FName& newTag) { WeaponTag = newTag; }

public:
	
	UFUNCTION(BlueprintPure)
	bool IsCanShoot();

	bool UseAmmo();

	void SetAmmo(int Ammo);



	UFUNCTION()
	void OnRep_Ammo();

	UPROPERTY(ReplicatedUsing = OnRep_Ammo)
	int m_Ammo;
	

};
