// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "AmmoBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// CDO 생성 및 컴포넌트 설정
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereCollision;
	//weapon
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComponent"));
	WeaponMesh->SetupAttachment(SphereCollision);
	if (WeaponMesh != nullptr)
	{
		WeaponMesh->SetSimulatePhysics(false);
	}
	WeaponMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	//bool
}
// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnWeaponBeingOverap);
}


// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AWeaponBase::WeaponShoot()
{

}

void AWeaponBase::OnWeaponBeingOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	OwnedCharacter = Cast<ACharacter>(OtherActor);
	if (IsValid(OwnedCharacter))
	{
		SetOwner(OwnedCharacter);
		UE_LOG(LogTemp, Warning, TEXT("SetOwner"));
		EquipWeapon();
	}
	
	

	
}

void AWeaponBase::EquipWeapon()
{
	if (IsValid(OwnedCharacter->GetOwner()))
	{
		UE_LOG(LogTemp, Warning, TEXT("True"));
		GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		UE_LOG(LogTemp, Warning, TEXT("DetachFromActor"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("False"));
	}

	this->AttachToComponent(OwnedCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHand")); 
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
	UE_LOG(LogTemp, Warning, TEXT("Attach")); 
	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
}
	

void AWeaponBase::Trigger()
{
	//soundspawn
	
	//TObjectPtr<USceneComponent> SaveLocation = WeaponMesh->GetSocketByName(TEXT("Muzzle"));
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),TriggerEffect,);
	//Bullet 생성
	GetWorld()->SpawnActor<AAmmoBase>();
}

