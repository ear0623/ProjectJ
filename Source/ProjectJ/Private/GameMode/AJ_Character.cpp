// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/AJ_Character.h"
#include "Camera/CameraComponent.h" //ī�޶�
#include "GameFramework/SpringArmComponent.h"//��������
#include "Components/CapsuleComponent.h" //ĸ��������Ʈ
#include "Components/SkeletalMeshComponent.h"//���̷�Ż�޽�
#include "EnhancedInputComponent.h"//���� �Է�
#include "Kismet/KismetMathLibrary.h"//ĳ���� ���� ȸ������ ���ϱ� ���� �ʿ�
#include "GameFramework/CharacterMovementComponent.h" // ĳ���� �����Ʈ�� �̿��ϱ� ���� �ʿ�
#include "Net/UnrealNetwork.h"//��������Ʈ���� �ʿ��� �ص�.
#include "Weapon/Public/WeaponBase.h" //
#include "Weapon/Public/WeaponBase.h"//puginWeapon






// Sets default values
AAJ_Character::AAJ_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SpringArm�̶�� �̸����� SpringArmComponent �߰�,RootConent�� �ڽ�����
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	//Camera��� �̸����� CameraComponent �߰�, SpringArm�� �ڽ�����
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	//ĳ���� �ʱ� ��ġ ��
	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	// ĳ���� �ʱ� ȸ����(Pitch, Yaw, Roll)
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
	
	//�ɱ� �ʱ� ��
	bIsCrouching = false; // �⺻���� fals�� �д�
	 
	//ĳ���� �޸��� �ӵ�
	SprintSpeedMultiplier = 2.0f; // �޸��� ���

	//bIsEquiped
	//Bool
	bIsEquiped = false;
}

// Called when the game starts or when spawned
void AAJ_Character::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAJ_Character::OnWeaponBeingOverap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AAJ_Character::OnWeaponEndOverap);
}

// Called every frame
void AAJ_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input �÷��̾� �Է¿� ���� ���ε� ����
void AAJ_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// ����ȯ�� ���ؼ� PlayerInputComponent �� UEnhancedInputComponent ������ ĳ����.
   // ��, ���� �Է� ����� �����ϴ� Ŀ���� �Է� ������Ʈ Ŭ������ UEnhancedInputComponent ��ĳ����.
	UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UEIC)
	{
		// ��ӹ��� AAJ_Character �� Jump ������ �Լ��� �̹� �ֱ� ������ AAJ_Character.h�� ABBC::Jump �Լ��� ������ �ʾƵ� ��
		
		//����
		UEIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &AAJ_Character::Jump);
		UEIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AAJ_Character::StopJumping);
		//����
		UEIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAJ_Character::Move);
		//��
		UEIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AAJ_Character::Look);
		//����
		UEIC->BindAction(IA_Trigger, ETriggerEvent::Started, this, &AAJ_Character::Trigger);
		//�ɱ�
		UEIC->BindAction(IA_Crouch, ETriggerEvent::Started, this, &AAJ_Character::StartCrouch);
		UEIC->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AAJ_Character::StopCrouching);
		//������
		UEIC->BindAction(IA_Reload, ETriggerEvent::Started, this, &AAJ_Character::Reload);
		//��ȣ�ۿ�
		UEIC->BindAction(IA_Interaction, ETriggerEvent::Started, this, &AAJ_Character::Interaction);
		//�޸���
		UEIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AAJ_Character::Sprint);
		UEIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AAJ_Character::StopSprint);
	}

}

/////////////////�Է� Ű �Լ� ����/////////////////////////////////////////////////////////

//����
void AAJ_Character::Move(const FInputActionValue& Value)
{
	// �Է°� Value �� ���� 2��(X, Y)������ ���� ����.
	FVector2d Dir = Value.Get<FVector2D>();

	//���� ��Ʈ�ѷ��� ȸ�� ���� �����ͼ� Yaw���� ����� ĳ���Ͱ� �ٶ󺸴� ������ ���Ѵ�.
	//Yaw�� �ش��ϴ� �� �̿ܿ��� 0�� �ִ� ������ Yaw���� ���ϱ� ����
	FRotator CameraRotation = GetControlRotation();
	FRotator DirectionRotation = FRotator(0, CameraRotation.Yaw, 0);
	
	//������ ���� �������� ĳ���Ͱ� �����ϴ� ������ ���Ͱ��� ���������� �̵��ϴ� ���Ͱ��� ���ϰԵ�.
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(DirectionRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(DirectionRotation);

	// ���� ������ ���Ϳ� ���� �̵� �Է� Dir.Y �� ���ؼ� �̵����� �߰�.
	AddMovementInput(ForwardVector, Dir.Y);
	// ���� ������ ���Ϳ� �¿� �̵� �Է� Dir.X �� ���ؼ� �̵����� �߰�.
	AddMovementInput(RightVector, Dir.X);
}

//��
void AAJ_Character::Look(const FInputActionValue& Value)
{
	// ĳ������ ȸ���� ���ؼ� �Է°����κ��� ���� ����.
	FVector2d Rotation = Value.Get<FVector2D>();

	// Yaw �� ����, Pitch �� ���� �̵����� �߰�.
	AddControllerYawInput(Rotation.X);
	AddControllerPitchInput(Rotation.Y);
}

//�ɱ�
void AAJ_Character::StartCrouch(const FInputActionValue& Value)
{
	if (!bIsCrouching)
	{ // �ɱ� �� ���� �� ����
		//OriginalCapsuleLocation = GetCapsuleComponent()->GetRelativeLocation();
		//OriginalCapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		// ��ġ, ���̰� ���ݾ� �پ���
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
		// �ɱ� �� ������� ������.
		//GetCapsuleComponent()->SetCapsuleHalfHeight(OriginalCapsuleHalfHeight);
		//GetCapsuleComponent()->SetRelativeLocation(OriginalCapsuleLocation);

	}
	PlayAnimMontage(StopCrouchMontage);
} 


//���� ����
void AAJ_Character::EquipWeapon(TSubclassOf<class AWeaponBase> WeaponClass)
{
	// ���� ���� �� ��ǥ �ʱⰪ ����
	m_EquipWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, FVector(0, 0, 0), FRotator(0, 0, 0));

	// ����ȯ ���ؼ� �������� ���� �� �ƹ��͵� ���� ����(return)
	AWeaponBase* pWeapon = Cast<AWeaponBase>(m_EquipWeapon);
	if (false == IsValid(pWeapon))
		return;

	pWeapon->m_pOwnChar = this;

	// �ӽ÷� Weapon ���̱� - SnapToTarget �� ���⸦ ���̵� �������� ������, ���� �̸��� Weapon
	m_EquipWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Weapon"));
	
	if (bIsEquiped == false)
	{
		bIsEquiped = true;
	};

}



//������
void AAJ_Character::Reload(const FInputActionValue& Value)
{
	ServerReload();
}

//����
void AAJ_Character::Trigger(const FInputActionValue& Value)
{
	ServerTrigger();
}

//���ͷ���
void AAJ_Character::Interaction(const FInputActionValue& Value)
{
	ServerInteraction();
	
}


//�޸���
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


/////////��Ʈ��ũ///////////////////////////////////////////////////////////////////



//����
void AAJ_Character::ServerTrigger_Implementation() 
{ 
	MultiTrigger();
}
void AAJ_Character::MultiTrigger_Implementation()
{
	PlayAnimMontage(TriggerMontage);
	
}

//������
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
	if (Weapon != nullptr)
	{
		Weapon->SetOwner(this); 
		Weapon->OwnedCharacter = this; 
		if (bIsEquiped == true)
		{
			//Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			bIsEquiped = false;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("DropWeapon")));
			Weapon->DropWeapon();
		}
		else
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
	
	//UE_LOG����
	//UE_LOG(LogTemp, Warning, TEXT("Current values are: vector %s, float %f, and integer %d"), *ExampleVector.ToString(), ExampleFloat, ExampleInteger);

}

void AAJ_Character::OnWeaponEndOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Weapon != nullptr)
	{
		Weapon->SetOwner(nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("EndOverrap")));
	}
	
}
