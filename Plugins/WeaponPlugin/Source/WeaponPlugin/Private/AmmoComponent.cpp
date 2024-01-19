// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoComponent.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
UAmmoComponent::UAmmoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo"));
	ArrowCompo = CreateDefaultSubobject<USceneComponent>(TEXT("Arrow"));

	//Vector Location =
	//ArrowCompo->AddRelativeLocation()
	//�ӵ�
	Velocity = 200;
	//�ӵ�X
	AccelateX = 0;
	//�ӵ�Y
	AccelateY = 0;
	//�е�
	AirDencity = 1;
	//�ܸ���
	CrossSectionalArea = 0;
	//�׷�
	Drag = 0;
	//�׷°��
	DragCoefficient = 0;
	//����
	Mass = 100;
	//���ӵ�
	Accelate = 0;
	//��
	Force = 0;
	//sin
	Sin = 30;
	//cos
	Cos = 30;


}


// Called when the game starts
void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAmmoComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAmmoComponent::BindState_Ammo()
{
}

void UAmmoComponent::SpawnAmmo()
{
	//GetWorld()->SpawnActor(AmmoMesh,)
}

void UAmmoComponent::Tirrger()
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

