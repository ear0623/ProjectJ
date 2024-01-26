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
	Velocity =200;
	//속도X
	AccelateX = 1;
	//속도Y
	AccelateY = 1;
	//속도Z
	AccelateZ = 1;
	//밀도
	AirDencity = 1;
	//단면적
	CrossSectionalArea = 1;
	//항력
	Drag = 1;
	//항력계수
	DragCoefficient = 1;
	//질량
	Mass =1;
	//가속도
	Accelate = 1;
	//힘
	Force = 1;
	//sin
	Sin = 30;
	//cos
	Cos = 30;
	//cos
	Tan = 30;


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
	
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT("%d"), SpawnRotation.Pitch));

	}

	
}


void UMagZineComponent::Fire(AWeaponBase* AWeaponBase)
{
	//FVector Aim = this->GetActorTransform().GetUnitAxis(EAxis::X);
//	FVector Location = GetActorLocation();
	
	float diameter = 5.56;
	CrossSectionalArea = FMath::Pow(diameter, 2) * 3.14 / 4;// 3.14 * (diameter * diameter) / 4;
	DragCoefficient = (Velocity * Velocity) * CrossSectionalArea * AirDencity * Drag / 2;
	Force = DragCoefficient;
	Accelate = Force / Mass;
	float SaveCos = cos(Cos);
	float SaveSin = sin(Sin);

	AccelateX = Accelate * SaveCos;
	AccelateY = Accelate * SaveSin - 9.8f;

	if (AWeaponBase&&SpawnedActor)
	{
		FVector FowardVector = SpawnedActor->GetActorForwardVector();
		FVector ActorLocation = SpawnedActor->GetActorLocation();
		float FowardX = FowardVector.X * AccelateX;
		FVector Impulse = FVector(FowardX, 0, AccelateY);
		FRotator DesiredRotation = FRotationMatrix::MakeFromX(Impulse).Rotator();
		SpawnedActor->SetActorRotation(DesiredRotation);
		SpawnedActor->AmmoMesh->AddImpulseAtLocation(Impulse,ActorLocation);
		//GEngine->AddOnScreenDebug
		// ]
		// Message(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT("X : %d ,Y : %d ,Z : %d"), Impulse.X, Impulse.Y, Impulse.Z));
	}
	
}

