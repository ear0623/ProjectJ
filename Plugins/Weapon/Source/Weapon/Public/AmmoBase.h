// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBase.generated.h"

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
	
////////////////////////////////����///////////////////////////
	//�ӵ�
	FVector Velocity;
	//�е�
	float Dencity;
	//�ܸ���
	float Cross_sectional_area;
	//�׷�
	float Drag;
	//�׷°��
	float Coefficient;
	//����
	float Mass;
	//���ӵ�
	float Accelate;
	//��
	float Force;
	//divide
	int32 Divide_half;
	//sin
	float Sin;
	//cos
	float Cos;
///////////////////////////////��Ÿ//////////////////////////
	//Damage
	float Damage;
	
public:

	void MoveAmmo();
	void Tirrger();

};
