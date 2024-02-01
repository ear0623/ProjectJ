// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ServerComponent.generated.h"

class SOCKET_API ISocketSubsystem;
class FSocket;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWWORK_API UServerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UServerComponent();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MadeSocket();
protected:
	


private:
	
	TObjectPtr<FSocket>ListenSocket;

	TObjectPtr<ISocketSubsystem> SocketSubsystem;

	TObjectPtr<FSocket> ClientSocket;

};
