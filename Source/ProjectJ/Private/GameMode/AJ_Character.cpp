// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/AJ_Character.h"
#include "Camera/CameraComponent.h" //카메라
#include "GameFramework/SpringArmComponent.h"//스프링암
#include "Components/CapsuleComponent.h" //캡슐컴포넌트
#include "Components/SkeletalMeshComponent.h"//스켈레탈메쉬
#include "EnhancedInputComponent.h"//향상된 입력
#include "Kismet/KismetMathLibrary.h"//캐릭터 기준 회전값을 구하기 위해 필요
#include "GameFramework/CharacterMovementComponent.h" // 캐릭터 무브먼트를 이용하기 위해 필요
#include "Weapon/Public/WeaponBase.h"//puginWeapon






// Sets default values
AAJ_Character::AAJ_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SpringArm이라는 이름으로 SpringArmComponent 추가,RootConent의 자식으로
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	//Camera라는 이름으로 CameraComponent 추가, SpringArm의 자식으로
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	//캐릭터 초기 위치 값
	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	// 캐릭터 초기 회전값(Pitch, Yaw, Roll)
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
	
	//앉기 초기 값
	bIsCrouching = false; // 기본값을 fals로 둔다
	 
	//캐릭터 달리기 속도
	SprintSpeedMultiplier = 2.0f; // 달리기 배속

	//Bool
	bIsEquiped = false;
}

// Called when the game starts or when spawned
void AAJ_Character::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAJ_Character::OnWeaponBeingOverap);
}

// Called every frame
void AAJ_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input 플레이어 입력에 대한 바인딩 설정
void AAJ_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 형변환을 통해서 PlayerInputComponent 를 UEnhancedInputComponent 형으로 캐스팅.
   // 즉, 향상된 입력 기능을 제공하는 커스텀 입력 컴포넌트 클래스인 UEnhancedInputComponent 로캐스팅.
	UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UEIC)
	{
		// 상속받은 AAJ_Character 에 Jump 관련한 함수는 이미 있기 때문에 AAJ_Character.h에 ABBC::Jump 함수를 만들지 않아도 됨
		
		//점프
		UEIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &AAJ_Character::Jump);
		UEIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AAJ_Character::StopJumping);
		//무브
		UEIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAJ_Character::Move);
		//룩
		UEIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AAJ_Character::Look);
		//공격
		UEIC->BindAction(IA_Trigger, ETriggerEvent::Started, this, &AAJ_Character::Trigger);
		//앉기
		UEIC->BindAction(IA_Crouch, ETriggerEvent::Started, this, &AAJ_Character::StartCrouch);
		UEIC->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AAJ_Character::StopCrouching);
		//재장전
		UEIC->BindAction(IA_Reload, ETriggerEvent::Started, this, &AAJ_Character::Reload);
		//상호작용
		UEIC->BindAction(IA_Interaction, ETriggerEvent::Started, this, &AAJ_Character::Interaction);
		//달리기
		UEIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AAJ_Character::Sprint);
		UEIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AAJ_Character::StopSprint);
	}

}

/////////////////입력 키 함수 설정/////////////////////////////////////////////////////////

//무브
void AAJ_Character::Move(const FInputActionValue& Value)
{
	// 입력값 Value 로 부터 2축(X, Y)형태의 값을 추출.
	FVector2d Dir = Value.Get<FVector2D>();

	//현재 컨트롤러의 회전 값을 가져와서 Yaw값만 사용해 캐릭터가 바라보는 방향을 구한다.
	//Yaw에 해당하는 값 이외에는 0을 넣는 이유는 Yaw값만 구하기 위함
	FRotator CameraRotation = GetControlRotation();
	FRotator DirectionRotation = FRotator(0, CameraRotation.Yaw, 0);
	
	//가져온 값을 바탕으로 캐릭터가 전진하는 방향의 벡터값과 오른쪽으로 이동하는 벡터값을 구하게됨.
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(DirectionRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(DirectionRotation);

	// 전진 방향의 벡터와 전후 이동 입력 Dir.Y 를 곱해서 이동값을 추가.
	AddMovementInput(ForwardVector, Dir.Y);
	// 우측 방향의 벡터와 좌우 이동 입력 Dir.X 를 곱해서 이동값을 추가.
	AddMovementInput(RightVector, Dir.X);
}

//룩
void AAJ_Character::Look(const FInputActionValue& Value)
{
	// 캐릭터의 회전을 위해서 입력값으로부터 값을 추출.
	FVector2d Rotation = Value.Get<FVector2D>();

	// Yaw 에 대한, Pitch 에 대한 이동값을 추가.
	AddControllerYawInput(Rotation.X);
	AddControllerPitchInput(Rotation.Y);
}

//앉기
void AAJ_Character::StartCrouch(const FInputActionValue& Value)
{
	if (!bIsCrouching)
	{ // 앉기 전 원본 값 저장
		//OriginalCapsuleLocation = GetCapsuleComponent()->GetRelativeLocation();
		//OriginalCapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		// 위치, 높이가 절반씩 줄어든다
		//GetCapsuleComponent()->SetCapsuleHalfHeight(OriginalCapsuleHalfHeight * 0.5f);
		//GetCapsuleComponent()->SetRelativeLocation(FVector(0.0f, 0.0f, OriginalCapsuleHalfHeight * 0.5f));
		Crouch();
		bIsCrouching = true;
	}
	PlayAnimMontage(CrouchMontage);
}
void AAJ_Character::StopCrouching(const FInputActionValue& Value)
{
	if (bIsCrouching)
	{	
		UnCrouch();
		bIsCrouching = false;
		// 앉기 전 사이즈로 돌린다.
		//GetCapsuleComponent()->SetCapsuleHalfHeight(OriginalCapsuleHalfHeight);
		//GetCapsuleComponent()->SetRelativeLocation(OriginalCapsuleLocation);

	}
	PlayAnimMontage(StopCrouchMontage);
}

//재장전
void AAJ_Character::Reload(const FInputActionValue& Value)
{
	ServerReload();
}

//공격
void AAJ_Character::Trigger(const FInputActionValue& Value)
{
	ServerTrigger();
}

//인터랙샨
void AAJ_Character::Interaction(const FInputActionValue& Value)
{
	ServerInteraction();
	
}


//달리기
void AAJ_Character::Sprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
	PlayAnimMontage(SprintMontage);
}

void AAJ_Character::StopSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
	PlayAnimMontage(StopSprintMontage);
}


/////////네트워크///////////////////////////////////////////////////////////////////



//공격
void AAJ_Character::ServerTrigger_Implementation() 
{ 
	MultiTrigger();
}
void AAJ_Character::MultiTrigger_Implementation()
{
	PlayAnimMontage(TriggerMontage);
}

//재장전
void AAJ_Character::ServerReload_Implementation()
{
	MultiReload();
	//character make variable->intputdata->weapon.h->delegate->equipWeapon
}
void AAJ_Character::MultiReload_Implementation()
{
	PlayAnimMontage(ReloadMontage);
}


void AAJ_Character::ServerInteraction_Implementation()
{
	
	MultiInteraction();
}

void AAJ_Character::MultiInteraction_Implementation()
{
	if (bIsEquiped == true)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		bIsEquiped = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("DropWeapon")));
		Weapon->DropWeapon();
	}
	if (Weapon != nullptr &&Weapon->GetOwner() == nullptr)
	{
		Weapon->SetOwner(this);
		Weapon->OwnedCharacter = this;
		if (bIsEquiped == false)
		{
			Weapon->EquipWeapon();
			bIsEquiped = true;
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("MultiInteraction_Implementation")));
}

void AAJ_Character::OnWeaponBeingOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%s"), *OtherActor->GetName()));
	Weapon = Cast<AWeaponBase>(OtherActor);
	
	//UE_LOG사용법
	//UE_LOG(LogTemp, Warning, TEXT("Current values are: vector %s, float %f, and integer %d"), *ExampleVector.ToString(), ExampleFloat, ExampleInteger);

}
