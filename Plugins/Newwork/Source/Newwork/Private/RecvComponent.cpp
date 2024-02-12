// Fill out your copyright notice in the Description page of Project Settings.


#include "RecvComponent.h"
#include "HAL/Runnable.h"

// Sets default values for this component's properties
URecvComponent::URecvComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Thread = FRunnableThread::Create(this, TEXT("NetworkThread"));
}

URecvComponent::~URecvComponent()
{
	if (Thread)
	{
		Thread->WaitForCompletion();
		Thread->Kill();
		delete Thread;
	}
}


// Called when the game starts
void URecvComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URecvComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool URecvComponent::Init()
{
	UE_LOG(LogNet, Warning, TEXT("Thread has been initialized"));
	return true;
}

uint32 URecvComponent::Run()
{
	while (true)
	{
		// Recv 작업을 여기서 진행 하면된다.
	}

	return 0;
}

void URecvComponent::Exit()
{
	
}

