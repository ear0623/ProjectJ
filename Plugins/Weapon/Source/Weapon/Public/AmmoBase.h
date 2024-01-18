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
	
////////////////////////////////���ӵ����///////////////////////////
	//�ӵ�
	float Velocity;
	//�ӵ�X
	float AccelateX;
	//�ӵ�Y
	float AccelateY;
	//�е�
	float AirDencity;
	//�ܸ���
	float CrossSectionalArea;
	//�׷�
	float Drag;
	//�׷°��
	float  DragCoefficient;
	//����
	float Mass;
	//���ӵ�
	float Accelate;
	//��
	float Force;
	//sin
	float Sin;
	//cos
	float Cos;
///////////////////////////////����//////////////////////////
	//Damage
	float Damage;
	
	////////Component///////////////////////////////////////////////////////////////////
	//����
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> AmmoMesh;

	//����Ÿ��
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	EBulletType AmmoType;

	TObjectPtr<AWeaponBase> Ammobase;
	
public:

	void MoveAmmo();

	void Tirrger();
	


};
