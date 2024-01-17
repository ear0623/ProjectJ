// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBase.h"


// Sets default values
AAmmoBase::AAmmoBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo"));
	RootComponent = AmmoMesh;

	//속도
	Velocity =200;
	//속도X
	AccelateX =0;
	//속도Y
	AccelateY =0;
	//밀도
	AirDencity=1;
	//단면적
	CrossSectionalArea=0;
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
	Sin =30;
	//cos
	Cos =30;



}

// Called when the game starts or when spawned
void AAmmoBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoBase::MoveAmmo()
{

}

void AAmmoBase::Tirrger()
{
	FVector Aim = this->GetActorTransform().GetUnitAxis(EAxis::X);
	FVector Location = GetActorLocation();
	float diameter=0;
	CrossSectionalArea = 3.14*(diameter*diameter) / 4;
	DragCoefficient = (Velocity * Velocity) * CrossSectionalArea * AirDencity * Drag / 2;
	Force=DragCoefficient;
	Accelate = Force / Mass;
	float SaveCos= cos(Cos);
	float SaveSin = sin(Sin);
	AccelateX = Accelate * SaveCos;
	AccelateY = Accelate * SaveSin-9.8f;

	AmmoMesh->AddImpulse(FVector(AccelateX,0,AccelateY));
}

