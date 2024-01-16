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
	PrimaryActorTick.bCanEverTick = true;
	// CDO 생성 및 컴포넌트 설정
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereCollision;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComponent"));
	WeaponMesh->SetupAttachment(SphereCollision);
	if (WeaponMesh != nullptr)
	{
		WeaponMesh->SetSimulatePhysics(true);
	}
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnWeaponBeingOverap);
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
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
	}
	
	
	if (OwnedCharacter != nullptr)
	{
		OwnedCharacter->AttachToComponent(OwnedCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("RightHand"));
		
		//AttachToActor(OwnedCharacter, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "RightHand");
		//OwnedCharacter->AttachToComponent(OwnedCharacter->GetMesh());
		UE_LOG(LogTemp, Warning, TEXT("Attach"));
	}

}

void AWeaponBase::Trigger()
{
	//soundspawn
	
	//TObjectPtr<USceneComponent> SaveLocation = WeaponMesh->GetSocketByName(TEXT("Muzzle"));
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),TriggerEffect,);
	//Bullet 생성
	GetWorld()->SpawnActor<AAmmoBase>();
}

