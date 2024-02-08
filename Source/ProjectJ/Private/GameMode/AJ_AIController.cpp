// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/AJ_AIController.h"
#include "GameMode/AJ_Character.h"
#include "Kismet/GameplayStatics.h" //UGameplayStatics
#include "GameFramework/Character.h"

AAJ_AIController::AAJ_AIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAJ_AIController::BeginPlay()
{
	Super::BeginPlay();
	FindRandomTarget();
}

void AAJ_AIController::Tick(float DelaTime)
{
	Super::Tick(DelaTime);

	if (IsValid(Target))
	{
		AttackTarget();
	}
	else
	{
		FindRandomTarget();
	}
}


// Target
void AAJ_AIController::FindRandomTarget()
{// Actor Found
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundActors);
	
	if (FoundActors.Num() > 0)
	{//Random Target Select
		Target = FoundActors[FMath::RandRange(0, FoundActors.Num() - 1)];
	}
}

void AAJ_AIController::AttackTarget()
{
	// Trigger 함수 완성되면 복붙하면 됨

}
