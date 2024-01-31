// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoBase.h"
#include "WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/DamageEvents.h" 
#include "Kismet/GameplayStatics.h"



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
	BulletMarks = UTexture2D::CreateTransient(100, 100);
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
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("SettingOwner_Implementation_Ammo"));
	if (this->GetOwner() == nullptr)
	{
		//this->SetOwner(character);
	}
	else
	{
		SetOwner(nullptr);
	}
}

void AAmmoBase::Hit_Implementation(AController* EventInstigator)
{
	FDamageEvent const& DamageEvent = { };
	TakeDamage(0, DamageEvent, EventInstigator, this);
}

void AAmmoBase::HitResult(FVector NormalImpulse)
{
	if (BulletMarks)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Hit")));
	}
}


float AAmmoBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) 
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); 
	switch (AmmoType) 
	{
	case EBulletType::AR_5:
		DamageAmount = 10;
		break;
	case EBulletType::AR_7:
		DamageAmount = 12;
		break;
	case EBulletType::AR_9:
		DamageAmount = 9;
		break;
		DamageAmount = 0;
	default:
		break;
	}
	Controller = EventInstigator;
	DamageCauser;


	TSubclassOf<UDamageType>DamageType;

	UGameplayStatics::ApplyDamage(this, DamageAmount, Controller, DamageCauser,DamageType);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("%s"),DamageCauser->GetClass()));

	return DamageAmount;
}

