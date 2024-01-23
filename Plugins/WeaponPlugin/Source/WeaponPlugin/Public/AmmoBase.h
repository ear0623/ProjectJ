// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponInterface.h"
#include "AmmoBase.generated.h"

class UStaticMeshComponent;
class AWeaponBase;
class IWeaponInterface;


UENUM(BlueprintType)
enum class EBulletType : uint8
{
	AR_5 UMETA(DisplayName = "5.56mm"),
	AR_7 UMETA(DisplayName = "7.62mm"),
	AR_9 UMETA(DisplayName = "9mm"),
};

UCLASS()
class WEAPONPLUGIN_API AAmmoBase : public AActor,public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//interface

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SettingOwner(ACharacter* character);

	void SettingOwner_Implementation(ACharacter* character);

	//FHitResult;

private:
	////////Component///////////////////////////////////////////////////////////////////
	//무기타입
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	EBulletType AmmoType;

public:
	//외형
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> AmmoMesh;

	

};
