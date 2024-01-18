// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBase.generated.h"

class UStaticMeshComponent;
class AWeaponBase;

UENUM(BlueprintType)
enum class EBulletType : uint8
{
	AR_5 UMETA(DisplayName = "5.56mm"),
	AR_7 UMETA(DisplayName = "7.62mm"),
	AR_9 UMETA(DisplayName = "9mm"),
};

UCLASS()
class WEAPON_API AAmmoBase : public AActor
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

private:
	
////////////////////////////////가속도계산///////////////////////////
	//속도
	float Velocity;
	//속도X
	float AccelateX;
	//속도Y
	float AccelateY;
	//밀도
	float AirDencity;
	//단면적
	float CrossSectionalArea;
	//항력
	float Drag;
	//항력계수
	float  DragCoefficient;
	//질량
	float Mass;
	//가속도
	float Accelate;
	//힘
	float Force;
	//sin
	float Sin;
	//cos
	float Cos;
///////////////////////////////변수//////////////////////////
	//Damage
	float Damage;
	
	////////Component///////////////////////////////////////////////////////////////////
	//외형
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> AmmoMesh;

	//무기타입
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	EBulletType AmmoType;

	TObjectPtr<AWeaponBase> Ammobase;
	
public:

	void MoveAmmo();

	void Tirrger();
	


};
