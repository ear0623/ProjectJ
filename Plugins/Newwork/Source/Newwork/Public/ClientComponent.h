// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClientComponent.generated.h"

class ISocketSubsystem;
class FSocket;
class FString;

struct NEWWORK_API FMessageHeader
{
	uint32 Type;
	uint32 Size;

	FMessageHeader(): Type(0), Size(0)
	{
	}

	FMessageHeader(uint32 Type, int32 PayloadSize)
		: Type(Type), Size(PayloadSize)
	{
	}

	friend FArchive& operator<<(FArchive& Ar, FMessageHeader& Header)
	{
		Ar << Header.Type;
		Ar << Header.Size;
		return Ar;
	}

	FMessageHeader(const uint32& Type, const uint32& Size)
		: Type(Type), Size(Size)
	{
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWWORK_API UClientComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClientComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void Connect();
public:
	static bool Receive(FSocket* Socket, uint8* Results, int32 Size);

	static bool Send(FSocket* Socket, const uint8* Buffer, int32 Size);

	static bool SendPacket(FSocket* Socket, uint32 Type, const TArray<uint8>& Payload);

	static bool SendPacket(FSocket* Socket, uint32 Type, const uint8* Payload, int32 PayloadSize);

	static bool ReceivePacket(FSocket* Socket, TArray<uint8>& OutPayload);

	UFUNCTION()
	void TestConnect();

	void Disconnect();

	void Send(uint32 Type, const FString& Text);

	void Recv();

	static bool Connecter(FSocket* Socket, FString IPAddress, int PortNumber);
	static void PrintSocketError(FString& OutText);
	static void DestroySocket(FSocket* Socket);

	
protected:
	bool bIsRunning;
private:
	FSocket* Socket;
public:
	FSocket* GetSocket() const { return Socket; }

};
