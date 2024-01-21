// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponInterface.h"
#include "MagZineComponent.generated.h"

class UStaticMeshComponent;
class AWeaponBase;
class IWeaponInterface;
class USceneComponent;

UENUM(BlueprintType)
enum class EBulletComponent : uint8
{
	AR_5 UMETA(DisplayName = "5.56mm"),
	AR_7 UMETA(DisplayName = "7.62mm"),
	AR_9 UMETA(DisplayName = "9mm"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEAPONPLUGIN_API UMagZineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMagZineComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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

	

public:
	void BindState_Ammo();

	UFUNCTION()
	void SpawnAmmo(const FVector& Location,const FRotator& Rotation);

	void Tirrger();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> AmmoMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneCompo;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Bullet;

	FVector SpawnLocation;

};
