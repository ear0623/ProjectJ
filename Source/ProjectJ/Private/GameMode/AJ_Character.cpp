// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/AJ_Character.h"
#include "Camera/CameraComponent.h" //Camera
#include "GameFramework/SpringArmComponent.h"//SpringArm
#include "Components/CapsuleComponent.h" //CapsuleComponent
#include "Components/SkeletalMeshComponent.h"//SkeletalMeshComponent
#include "EnhancedInputComponent.h"//EnhancedInput
#include "Kismet/KismetMathLibrary.h" //Character Rotation value
#include "GameFramework/CharacterMovementComponent.h" //CharacterMovementComponent
#include "Net/UnrealNetwork.h"//
#include "WeaponInterface.h"
#include "WeaponBase.h"
#include "AmmoBase.h"

// Sets default values
AAJ_Character::AAJ_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SpringArm 
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	//Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	// Character initial position value
	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	// Character initial Rotation value
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
	
	// Crouch variables
	bIsCrouching = false;
	 
	//Sprint Velocity
	SprintSpeedMultiplier = 2.0f;

	//Equip variables 
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

// Bind Input
void AAJ_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UEIC)
	{
		
		
		//Jump
		UEIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &AAJ_Character::Jump);
		UEIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AAJ_Character::StopJumping);
		//Move
		UEIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAJ_Character::Move);
		//Look
		UEIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AAJ_Character::Look);
		//Trigger
		UEIC->BindAction(IA_Trigger, ETriggerEvent::Started, this, &AAJ_Character::Trigger);
		//Crouch
		UEIC->BindAction(IA_Crouch, ETriggerEvent::Started, this, &AAJ_Character::StartCrouch);
		UEIC->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AAJ_Character::StopCrouching);
		//Reload
		UEIC->BindAction(IA_Reload, ETriggerEvent::Started, this, &AAJ_Character::Reload);
		//Interaction
		UEIC->BindAction(IA_Interaction, ETriggerEvent::Started, this, &AAJ_Character::Interaction);
		
		UEIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AAJ_Character::Sprint);
		UEIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AAJ_Character::StopSprint);
	}

}



// Move

void AAJ_Character::Move(const FInputActionValue& Value)
{
	// �Է°� Value �� ���� 2��(X, Y)������ ���� ����.
	FVector2d Dir = Value.Get<FVector2D>();


	FRotator CameraRotation = GetControlRotation();
	FRotator DirectionRotation = FRotator(0, CameraRotation.Yaw, 0);
	

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(DirectionRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(DirectionRotation);


	AddMovementInput(ForwardVector, Dir.Y);
	
	AddMovementInput(RightVector, Dir.X);
}

// Look
//��
void AAJ_Character::Look(const FInputActionValue& Value)
{
	// ĳ������ ȸ���� ���ؼ� �Է°����κ��� ���� ����.
	FVector2d Rotation = Value.Get<FVector2D>();

	// Yaw �� ����, Pitch �� ���� �̵����� �߰�.
	AddControllerYawInput(Rotation.X);
	AddControllerPitchInput(Rotation.Y);
}



// Crouch
//�ɱ�
void AAJ_Character::StartCrouch(const FInputActionValue& Value)
{
	if (!bIsCrouching)
	{
		//OriginalCapsuleLocation = GetCapsuleComponent()->GetRelativeLocation();
		//OriginalCapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		// ��ġ, ���̰� ���ݾ� �پ���
		//GetCapsuleComponent()->SetCapsuleHalfHeight(OriginalCapsuleHalfHeight * 0.5f);
		//GetCapsuleComponent()->SetRelativeLocation(FVector(0.0f, 0.0f, OriginalCapsuleHalfHeight * 0.5f));
		//Crouch();
		bIsCrouching = true;
	}
	PlayAnimMontage(CrouchMontage);
}

void AAJ_Character::StopCrouching(const FInputActionValue & Value)
{
	if (bIsCrouching)
	{
		bIsCrouching = false;
		//GetCapsuleComponent()->SetCapsuleHalfHeight(OriginalCapsuleHalfHeight);
		//GetCapsuleComponent()->SetRelativeLocation(OriginalCapsuleLocation);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("falseline")));
	}

}


//������
void AAJ_Character::Reload(const FInputActionValue& Value)
{
	ServerReload();
}

// Trigger
//����
void AAJ_Character::Trigger(const FInputActionValue& Value)
{
	ServerTrigger();
}

//Interaction
void AAJ_Character::Interaction(const FInputActionValue& Value)
{
	ServerInteraction();
}


//Sprint
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

///////////////////////////////////////////////////////////Network////////////////////////////////////////////////////////////////////////////////////////////
//Trigger
void AAJ_Character::ServerTrigger_Implementation()
{
	MultiTrigger();
}
	
void AAJ_Character::MultiTrigger_Implementation()
{
	PlayAnimMontage(TriggerMontage);
	
	if (WeaponData != nullptr)
	{
		IWeaponInterface* CallWeaponInterface = Cast<IWeaponInterface>(this);
		CallWeaponInterface->Execute_WeaponShoot(WeaponClass);
	}
	
}
//Reload
void AAJ_Character::ServerReload_Implementation()
{
	MultiReload();
	
}
void AAJ_Character::MultiReload_Implementation()
{
	PlayAnimMontage(ReloadMontage);
}


//Interaction
void AAJ_Character::ServerInteraction_Implementation()
{
	MultiInteraction();
}

void AAJ_Character::MultiInteraction_Implementation()
{
	if (WeaponData != nullptr)
	{
		AAmmoBase* ammoClass = Cast<AAmmoBase>(WeaponClass);
		WeaponData->Execute_SettingOwner(WeaponClass,this);
		//WeaponData->Execute_SettingOwner_If_OnlyOne(ammoClass, this);
		//WeaponData->OwnedCharacter = this;
		if (bIsEquiped == true)
		{
			bIsEquiped = false;
			WeaponData->Execute_DropWeapon(WeaponClass);
			WeaponData = nullptr;
		}
		else
		{
			//무기를 들고있을 경우 drop처리
			WeaponData->Execute_EquipWeapon(WeaponClass);
			bIsEquiped = true;
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("MultiInteraction_Implementation")));
}

void AAJ_Character::OnWeaponBeingOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%s"), *OtherActor->GetName()));
	WeaponClass = Cast<AWeaponBase>(OtherActor);
	WeaponData = Cast<IWeaponInterface>(OtherActor);

	
	//UE_LOG����
	//UE_LOG(LogTemp, Warning, TEXT("Current values are: vector %s, float %f, and integer %d"), *ExampleVector.ToString(), ExampleFloat, ExampleInteger);

}

void AAJ_Character::OnWeaponEndOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (WeaponData != nullptr)
	{
		WeaponData->Execute_ClearOwner(WeaponClass);
	}
	
}

