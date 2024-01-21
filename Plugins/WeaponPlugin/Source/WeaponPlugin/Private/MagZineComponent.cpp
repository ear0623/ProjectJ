// Fill out your copyright notice in the Description page of Project Settings.


#include "MagZineComponent.h"
#include "Components/SceneComponent.h"


// Sets default values for this component's properties
UMagZineComponent::UMagZineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SpawnLocation = { 0, 0, 0 };
	//속도
	Velocity = 200;
	//속도X
	AccelateX = 0;
	//속도Y
	AccelateY = 0;
	//밀도
	AirDencity = 1;
	//단면적
	CrossSectionalArea = 0;
	//항력
	Drag = 0;
	//항력계수
	DragCoefficient = 0;
	//질량
	Mass = 100;
	//가속도
	Accelate = 0;
	//힘
	Force = 0;
	//sin
	Sin = 30;
	//cos
	Cos = 30;


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
	
	TObjectPtr<AActor> spawnedActor= GetWorld()->SpawnActor<AActor>(Bullet,SpawnTransform,ActorSpawnParamers);
	if (spawnedActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT("spawnedActor")));
	}

	
}

void UMagZineComponent::Tirrger()
{
	//FVector Aim = this->GetActorTransform().GetUnitAxis(EAxis::X);
//	FVector Location = GetActorLocation();
	float diameter = 0;
	CrossSectionalArea = 3.14 * (diameter * diameter) / 4;
	DragCoefficient = (Velocity * Velocity) * CrossSectionalArea * AirDencity * Drag / 2;
	Force = DragCoefficient;
	Accelate = Force / Mass;
	float SaveCos = cos(Cos);
	float SaveSin = sin(Sin);
	AccelateX = Accelate * SaveCos;
	AccelateY = Accelate * SaveSin - 9.8f;

	//AmmoMesh->AddImpulse(FVector(AccelateX, 0, AccelateY));
}

