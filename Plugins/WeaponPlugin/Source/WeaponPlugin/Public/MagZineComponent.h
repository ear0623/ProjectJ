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
class AAmmoBase;
class WeaponBase;

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

	////////////////////////////////가속도계산///////////////////////////
		//속도
	float Velocity;
	//속도X
	float AccelateX;
	//속도Y
	float AccelateY;
	//속도Z
	float AccelateZ;
	//밀도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable",meta = (AllowPrivateAccess = "true"))
	float AirDencity;
	//단면적
	float CrossSectionalArea;
	//항력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (AllowPrivateAccess = "true"))
	float Drag;
	//항력계수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (AllowPrivateAccess = "true"))
	float  DragCoefficient;
	//질량
	float Mass;
	//가속도
	float Accelate;
	//힘
	float Force;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (AllowPrivateAccess = "true"))
	float diameter;
	///////////////////////////////변수//////////////////////////
		//Damage
	float Damage;

	

public:
	void BindState_Ammo();

	UFUNCTION()
	void SpawnAmmo(const FVector& Location,const FRotator& Rotation);

	void Fire(AWeaponBase* AWeaponBase,const FVector &Center);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> AmmoMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneCompo;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponComponents", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAmmoBase> Bullet;

	FVector SpawnLocation;

	TObjectPtr<AAmmoBase> SpawnedActor;

};
