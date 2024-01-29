// Fill out your copyright notice in the Description page of Project Settings.


#include "MagZineComponent.h"
#include "Components/SceneComponent.h"
#include "WeaponPlugin/Public/AmmoBase.h"
#include "WeaponBase.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UMagZineComponent::UMagZineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SpawnLocation = { 0, 0, 0 };
	//속도
	Velocity =450;
	//속도X
	AccelateX = 1;
	//속도Y
	AccelateY = 1;
	//속도Z
	AccelateZ = 1;
	//밀도
	AirDencity = 1.225f;
	//단면적
	CrossSectionalArea = 1;
	//항력
	Drag = 1;
	//항력계수
	DragCoefficient = 0.3;
	//질량
	Mass =1;
	//가속도
	Accelate = 1;
	//힘
	Force = 1;
	//sin
	Sin = 30;
	//cos
	Cos = 60;
	//cos
	Tan = 90;


}


// Called when the game starts
void UMagZineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMagZineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMagZineComponent::BindState_Ammo()
{
}

void UMagZineComponent::SpawnAmmo(const FVector& Location, const FRotator& Rotation)
{
	SpawnLocation = Location;
	FRotator SpawnRotation = Rotation;
	FTransform SpawnTransform = { SpawnRotation,SpawnLocation,FVector(1.0f,1.0f,1.0f) };
	FActorSpawnParameters ActorSpawnParamers;
	ActorSpawnParamers.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	SpawnedActor= GetWorld()->SpawnActor<AAmmoBase>(Bullet,SpawnTransform,ActorSpawnParamers);
	if (SpawnedActor)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT("%d"), SpawnRotation.Pitch));
	}

	
}


void UMagZineComponent::Fire(AWeaponBase* WeaponBase, const FVector& Center)
{
	float diameter = 0.556;
	CrossSectionalArea = FMath::Pow(diameter, 2) * 3.14 / 4;// 3.14 * (diameter * diameter) / 4;
	DragCoefficient=0.3f;
	Force = DragCoefficient * FMath::Pow(Velocity,2) * CrossSectionalArea * AirDencity * Drag / 2;
	
	Accelate = Force / Mass;
	
	if (WeaponBase&&SpawnedActor)
	{
		FVector FowardVector = WeaponBase->GetActorForwardVector(); 
		FVector FRightVector = WeaponBase->GetActorRightVector(); 
		FVector FUpVector = WeaponBase->GetActorUpVector(); 

		AccelateX = Accelate;
		AccelateY = Accelate;
		AccelateZ = Accelate - 9.8f;

		FVector ActorLocation = SpawnLocation;//prefab? componentbase; unity

		FVector WeaponXAixs = FowardVector;
		FVector WeaponYAixs = FRightVector;
		FVector WeaponZAxis = FUpVector;//FVector::CrossProduct(FRightVector, FowardVector);//외적계산
		//vector의 합산
		FVector AxisY = (AccelateY * WeaponYAixs);
		FVector AxisX = (AccelateX * WeaponXAixs);
		FVector Impulse = Accelate*(FowardVector);
	
		//FVector WorldImpulse = WeaponBase->GetTransform().TransformVectorNoScale(AxisX);
		FRotator DesiredRotation = WeaponXAixs.Rotation() + WeaponYAixs.Rotation(); 
		SpawnedActor->SetActorRotation(WeaponXAixs.Rotation());
		SpawnedActor->AmmoMesh->AddImpulse(Impulse);

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%lf"), WeaponXAixs.X));

	}
	
}

