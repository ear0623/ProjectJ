// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "AmmoBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"//델리게이트사용시 필요한 해드.


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
	}
	WeaponMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	//
	SetReplicates(true);
}
// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}


//기준(1상속 원칙)-> 상속 혹은 여러cpp에서 일괄적으로 처리하고싶어.(약한 관계성을 만들기위에)
void AWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	
}

void AWeaponBase::WeaponShoot()
{

}

void AWeaponBase::EquipWeapon_Implementation()
{
	/*SphereCollision->SetSimulatePhysics(false);
	WeaponMesh->SetSimulatePhysics(false);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
	this->AttachToComponent(OwnedCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHand"));
	UE_LOG(LogTemp, Warning, TEXT("Attach"));	*/
	EquipWeapon_Multicast();
}

void AWeaponBase::EquipWeapon_Multicast_Implementation() 
{
	SphereCollision->SetSimulatePhysics(false);
	WeaponMesh->SetSimulatePhysics(false);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
	this->AttachToComponent(OwnedCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHand"));
	UE_LOG(LogTemp, Warning, TEXT("Attach"));
}

void AWeaponBase::DropWeapon_Implementation()
{
	//SphereCollision->SetSimulatePhysics(true);
	WeaponMesh->SetSimulatePhysics(true);
	//SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponMesh->SetCollisionProfileName(TEXT("WeaponPresets"));
	//DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	UE_LOG(LogTemp, Warning, TEXT("Detach"));
	SetOwner(nullptr);
}
	

void AWeaponBase::Trigger()
{
	//soundspawn
	
	//TObjectPtr<USceneComponent> SaveLocation = WeaponMesh->GetSocketByName(TEXT("Muzzle"));
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),TriggerEffect,);
	//Bullet 생성
	GetWorld()->SpawnActor<AAmmoBase>();
}


