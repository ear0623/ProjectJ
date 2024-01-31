// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicActor.h"
#include "Ammobase.h"

// Sets default values
ADynamicActor::ADynamicActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADynamicActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorHit.AddDynamic(this, &ADynamicActor::MakeTexture);

	
}

// Called every frame
void ADynamicActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADynamicActor::MakeTexture(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	Ammobase = Cast<AAmmoBase>(OtherActor);
	if (Ammobase)
	{

		Ammobase->HitResult(NormalImpulse);
	}
}

