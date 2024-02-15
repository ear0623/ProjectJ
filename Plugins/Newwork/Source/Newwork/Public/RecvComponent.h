// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecvComponent.generated.h"

class FRunnable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWWORK_API URecvComponent : public UActorComponent , public FRunnable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecvComponent();
	~URecvComponent()override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	bool Init() override;
	uint32 Run() override;
	void Exit() override;



private:
	FRunnableThread* Thread;

};
