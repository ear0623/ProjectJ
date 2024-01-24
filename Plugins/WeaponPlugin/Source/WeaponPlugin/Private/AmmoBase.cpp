// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBase.h"
#include "WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/DamageEvents.h" 



// Sets default values
AAmmoBase::AAmmoBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//componenet
	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoComponent"));
	RootComponent =AmmoMesh;
	FVector BulletForwardVector = GetActorForwardVector();
	FRotator MuzzleRotation = FRotator(BulletForwardVector.X, 0, 0);
	AmmoMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AAmmoBase::BeginPlay()
{
	Super::BeginPlay();
	
	//Ammobase->Trigger().AddDynamic();
}

// Called every frame
void AAmmoBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAmmoBase::SettingOwner_Implementation(ACharacter* character)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("SettingOwner_Implementation_Ammo"));
	if (this->GetOwner() == nullptr)
	{
		//this->SetOwner(character);
	}
	else
	{
		SetOwner(nullptr);
	}
}


//float AAmmoBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
//{
//	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
//
//	
//	DamageAmount;
//	Controller = EventInstigator;
//	DamageCauser;
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("TakeDamage"));
//
//	return 0.0f;
//}

