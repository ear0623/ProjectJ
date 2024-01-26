// Fill out your copyright notice in the Description page of Project Settings.


#include "MagZineComponent.h"
#include "Components/SceneComponent.h"
#include "WeaponPlugin/Public/AmmoBase.h"
#include "WeaponBase.h"


// Sets default values for this component's properties
UMagZineComponent::UMagZineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SpawnLocation = { 0, 0, 0 };
	//속도
	Velocity =900;
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


void UMagZineComponent::Fire(AWeaponBase* AWeaponBase)
{
	//FVector Aim = this->GetActorTransform().GetUnitAxis(EAxis::X);
//	FVector Location = GetActorLocation();
	
	float diameter = 0.556;
	CrossSectionalArea = FMath::Pow(diameter, 2) * 3.14 / 4;// 3.14 * (diameter * diameter) / 4;
	DragCoefficient=0.3f;
	Force = DragCoefficient * FMath::Pow(Velocity,2) * CrossSectionalArea * AirDencity * Drag / 2;
	
	Accelate = Force / Mass;
	

	if (AWeaponBase&&SpawnedActor)
	{
		FVector FowardVector = AWeaponBase->GetActorForwardVector();
		FVector FRightVector = AWeaponBase->GetActorRightVector();
		FVector FUpVector = AWeaponBase->GetActorUpVector();

		float SaveCos = -FVector::DotProduct(FVector::RightVector,FowardVector);

		float SaveSin = -FVector::DotProduct(FVector::UpVector,FowardVector);

		AccelateX = Accelate * SaveCos;
		AccelateY = Accelate * SaveSin - 9.8f;

		FVector ActorLocation = SpawnLocation;

		FVector WeaponXAixs = FowardVector;
		FVector WeaponYAixs = FRightVector;
		FVector WeaponZAxis = FVector::CrossProduct(FRightVector, FowardVector);//외적계산
		//vector의 합산
		FVector Impulse = (AccelateX * WeaponXAixs) +(AccelateY * WeaponZAxis); //
		FRotator DesiredRotation = WeaponXAixs.Rotation() + WeaponYAixs.Rotation(); 
		SpawnedActor->SetActorRotation(WeaponXAixs.Rotation());
		SpawnedActor->AmmoMesh->AddImpulse(Impulse);

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("X : %lf ,Y : %lf ,Z : %lf"), Impulse.X, Impulse.Y, Impulse.Z));
	}
	
}

