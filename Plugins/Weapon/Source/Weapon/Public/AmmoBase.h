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
	
////////////////////////////////인자///////////////////////////
	//속도
	FVector Velocity;
	//밀도
	float Dencity;
	//단면적
	float Cross_sectional_area;
	//항력
	float Drag;
	//항력계수
	float Coefficient;
	//질량
	float Mass;
	//가속도
	float Accelate;
	//힘
	float Force;
	//divide
	int32 Divide_half;
	//sin
	float Sin;
	//cos
	float Cos;
///////////////////////////////기타//////////////////////////
	//Damage
	float Damage;
	
public:

	void MoveAmmo();
	void Tirrger();

};
