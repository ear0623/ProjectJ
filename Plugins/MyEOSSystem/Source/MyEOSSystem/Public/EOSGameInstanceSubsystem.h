// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EOSGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYEOSSYSTEM_API UEOSGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,Category ="EosDedicatedserver")
	void CreateDedicateServerSession();
};
