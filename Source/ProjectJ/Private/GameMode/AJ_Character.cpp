// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/AJ_Character.h"
#include "Camera/CameraComponent.h" //ī�޶�
#include "GameFramework/SpringArmComponent.h"//��������
#include "Components/CapsuleComponent.h" //ĸ��������Ʈ
#include "Components/SkeletalMeshComponent.h"//���̷�Ż�޽�
#include "EnhancedInputComponent.h"//���� �Է�
#include "Kismet/KismetMathLibrary.h"//ĳ���� ���� ȸ������ ���ϱ� ���� �ʿ�


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
	//
}

// Called when the game starts or when spawned
void AAJ_Character::BeginPlay()
{
	Super::BeginPlay();
	
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
		UEIC->BindAction(IA_Shoot, ETriggerEvent::Started, this, &AAJ_Character::Shoot);
		//�ɱ�
		UEIC->BindAction(IA_Crouch, ETriggerEvent::Started, this, &AAJ_Character::Crouch);
		UEIC->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AAJ_Character::StopCrouching);
		//������
		UEIC->BindAction(IA_Reload, ETriggerEvent::Started, this, &AAJ_Character::Reload);
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
void AAJ_Character::Crouch(const FInputActionValue& Value)
{
	ServerCrouch();
}
void AAJ_Character::StopCrouching(const FInputActionValue& Value)
{
}

//������
void AAJ_Character::Reload(const FInputActionValue& Value)
{
	ServerReload();
}

//����
void AAJ_Character::Shoot(const FInputActionValue& Value)
{
	ServerShoot();
}


/////////��Ʈ��ũ///////////////////////////////////////////////////////////////////

//�ɱ�
void AAJ_Character::ServerCrouch_Implementation()
{
	MultiCrouch();
}
void AAJ_Character::MultiCrouch_Implementation()
{
}

//����
void AAJ_Character::ServerShoot_Implementation()
{
	UpdateShoot.Execute();
	MultiShoot();
}
void AAJ_Character::MultiShoot_Implementation()
{
	PlayAnimMontage(ShootMontage);
}

//������
void AAJ_Character::ServerReload_Implementation()
{
	MultiReload();
}
void AAJ_Character::MultiReload_Implementation()
{
	PlayAnimMontage(ReloadMontage);
}

