// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerPlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class PROJECTJ_API APlayerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")
	TObjectPtr<UInputMappingContext> DefaultIMC;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(Client, Reliable)
	void ResClientPossess();
};
