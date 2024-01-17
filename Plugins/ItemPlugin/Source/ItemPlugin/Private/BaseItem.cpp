// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"


// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 헤더에서 만든 변수 StaticMesh 에 Mesh 라는 이름으로 StaticMeshComponent 를 추가합니다.
	// 이후에 해당 StaticMesh 의 시뮬레이트 피직스를 활성화 해줍니다.
	m_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	m_Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	// StaticMesh 를 트리구조에서 최상위 컴포넌트로 해줍니다.
	SetRootComponent(m_StaticMesh);
	SetRootComponent(m_Scene);
	m_StaticMesh->SetupAttachment(m_Scene);
	m_StaticMesh->SetCollisionProfileName("OverlapAllDynamic");


	// 리플리케이트 옵션을 활성화 해주고 Movement 리플리케이트도 활성화 해줍니다.
	bReplicates = true;
	SetReplicateMovement(true);

	m_StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemBeginOverlap);
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_StaticMesh->AddRelativeRotation(FRotator(0.0f, 1.0f, 0.0f));

}

void ABaseItem::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IItemInterface* InterfaceObj = Cast<IItemInterface>(OtherActor);

	if (nullptr == InterfaceObj)
		return;

	// 인터페이스 호출 - 인자값(객체), 파라미터(우리는 사용하지 않아서 없음)
	InterfaceObj->Execute_EventGetItem(OtherActor,m_eItemType);
	
}

