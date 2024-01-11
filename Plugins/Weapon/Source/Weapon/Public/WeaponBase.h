// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponInterface.h"
#include "WeaponBase.generated.h"

class UStaticMeshComponent;


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

	//외형
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	//무기타입
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;


public:
	/////////인터페이스///////////////////////////////////////////////////////////////////
	virtual void WeaponShoot()override;
};
