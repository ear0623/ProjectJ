// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "AmmoBase.h"
#include "Kismet/GameplayStatics.h"
#include "MagZineComponent.h"



// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// CDO 생성 및 컴포넌트 설정
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereCollision;
	if (SphereCollision)
	{
		SphereCollision->SetSimulatePhysics(true);
		SphereCollision->SetCollisionProfileName("WeaponPresets");
	}
	//weapon
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComponent"));
	WeaponMesh->SetupAttachment(SphereCollision);
	if (WeaponMesh != nullptr)
	{
		WeaponMesh->SetSimulatePhysics(false);
		WeaponMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	}
	MagzineCompo = CreateDefaultSubobject<UMagZineComponent>(TEXT("MazgineComponent"));
	//replicated
	SetReplicates(true);
	SphereCollision->SetIsReplicated(true);
	WeaponMesh->SetIsReplicated(true);

	//Tag
	WeaponTag = FName(TEXT("Weapon"));
}
// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}



void AWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(AWeaponBase, m_Mag);
}

void AWeaponBase::WeaponShoot_Implementation()
{
	Trigger();
}

void AWeaponBase::SettingOwner_Implementation(ACharacter* character)
{
	this->SetOwner(character);
	OwnedCharacter = character;
	
}

void AWeaponBase::ClearOwner_Implementation()
{
	this->SetOwner(nullptr);
	//OwnedCharacter = nullptr;
}

void AWeaponBase::EquipWeapon_Implementation()
{
	EquipWeapon_Server();
}
void AWeaponBase::EquipWeapon_Server_Implementation()
{
	EquipWeapon_Multicast();
}

void AWeaponBase::EquipWeapon_Multicast_Implementation()
{
	if (GetAttachParentSocketName() == NAME_None&&OwnedCharacter)
	{
		
		SphereCollision->SetSimulatePhysics(false);
		WeaponMesh->SetSimulatePhysics(false);
		SphereCollision->SetCollisionProfileName("NoCollision");
		WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
		this->AttachToComponent(OwnedCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHand")); 
	}
}

void AWeaponBase::DropWeapon_Implementation()
{
	DropWeapon_Multicast();
}


void AWeaponBase::DropWeapon_Multicast_Implementation()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform); 
	SphereCollision->SetSimulatePhysics(true);
	WeaponMesh->SetSimulatePhysics(false);
	SphereCollision->SetCollisionProfileName("WeaponPresets");
	WeaponMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	SetOwner(nullptr);
	if (OwnedCharacter != nullptr)
	{
		OwnedCharacter = nullptr;
	}
	
}

void AWeaponBase::Trigger()
{
	FVector MuzzleLocation= WeaponMesh->GetSocketLocation((TEXT("Muzzle")));
	FVector BulletForwardVector = WeaponMesh->GetSocketTransform(TEXT("Muzzle")).GetUnitAxis(EAxis::X);
	FRotator MuzzleRotation = FRotator(BulletForwardVector.X,0,0);
	FTransform MuzleTransfrom = { MuzzleRotation,MuzzleLocation, FVector(1.0f,1.0f,1.0f)}; 

	FVector SenterSocket = WeaponMesh->GetSocketLocation(TEXT("Senter"));
	
	if (TriggerEffect != nullptr)
	{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TriggerEffect, MuzleTransfrom);
	}
	FHitResult OutHit;
	FVector EndLocation = FVector(MuzzleLocation + (this->GetActorForwardVector()*100000));
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	bool RayResult = GetWorld()->LineTraceSingleByChannel(OutHit, MuzzleLocation,EndLocation, ECollisionChannel::ECC_Camera, Params);
	if (RayResult)
	{
		
	}
	//Bullet 생성
	MagzineCompo->SpawnAmmo(MuzzleLocation, MuzzleRotation); 
	MagzineCompo->Fire(this, MuzzleLocation);
	
	UseAmmo();
}

bool AWeaponBase::IsCanShoot()
{
	if (m_Ammo <= 0)
		return false;

	
	return true;
}

bool AWeaponBase::UseAmmo()
{
	if (false == IsCanShoot())
		return false;
	m_Ammo = m_Ammo - 1;
	m_Ammo = FMath::Clamp(m_Ammo, 0, 30);

	OnRep_Ammo();

	return true;
}

void AWeaponBase::SetAmmo(int Ammo)
{
	m_Ammo = Ammo;

	OnRep_Ammo();
}

void AWeaponBase::OnRep_Ammo()
{

}

void AWeaponBase::Cur_Mag()
{
	int32 MagValue = 10;
	
	OnUpdateMag.Broadcast(MagValue);
}


