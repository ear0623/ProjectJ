// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "AJ_AIController.generated.h"



UCLASS()
class PROJECTJ_API AAJ_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAJ_AIController();

	virtual void BeginPlay() override;
	virtual void Tick(float DelaTime) override;
	
	//Target Searching
	void FindRandomTarget();
	//Target Attack
	void AttackTarget();

	// Selected Target
	AActor* Target;
};
