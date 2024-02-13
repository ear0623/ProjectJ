// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/AJ_Character.h"
#include "GameFramework/Actor.h"
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
#include "Kismet/GameplayStatics.h"
#include "Widget/Player/PlayerPlayerState.h"
#include "Blueprint/UserWidget.h"

#include "GameMode/AJ_AIController.h"





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

	//Crouch value
	bIsCrouching = false;

	//Equip Value
	bIsEquiped = false;

	//Sprint 
	SprintSpeedMultiplier = 1.5f; //Sprint Speed
	bIsSprint = false;//Spint valuables value
	AJDefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed; //DefaultSpeed

	//Parkour 
	bIsParkour = false;

	//Dead
	bIsDead = false;

	//IsSprint?
	bIsSprintKeyPressed = false;
}

// Called when the game starts or when spawned
void AAJ_Character::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAJ_Character::OnWeaponBeingOverap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AAJ_Character::OnWeaponEndOverap);
	GetWorldTimerManager().SetTimer(STMUTimerHandle, this, &AAJ_Character::STMUTimer, 0.1f, true);
	Dead();
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
		//Sprint
		UEIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AAJ_Character::Sprint);
		UEIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AAJ_Character::StopSprint);
		//Parkour
		UEIC->BindAction(IA_Parkour, ETriggerEvent::Started, this, &AAJ_Character::Parkour);
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
void AAJ_Character::Look(const FInputActionValue& Value)
{
	// ĳ������ ȸ���� ���ؼ� �Է°����κ��� ���� ����.
	FVector2d Rotation = Value.Get<FVector2D>();

	// Yaw �� ����, Pitch �� ���� �̵����� �߰�.
	AddControllerYawInput(Rotation.X);
	AddControllerPitchInput(Rotation.Y);
}



// Crouch
void AAJ_Character::StartCrouch(const FInputActionValue& Value)
{
	ServerStartCrouch();
	//if (!bIsCrouching)
	//{
		//OriginalCapsuleLocation = GetCapsuleComponent()->GetRelativeLocation();
		//OriginalCapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		// ��ġ, ���̰� ���ݾ� �پ���
		//GetCapsuleComponent()->SetCapsuleHalfHeight(OriginalCapsuleHalfHeight * 0.5f);
		//GetCapsuleComponent()->SetRelativeLocation(FVector(0.0f, 0.0f, OriginalCapsuleHalfHeight * 0.5f));
		//Crouch();
		//bIsCrouching = true;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("StartCrouch!")));
	//}

}
void AAJ_Character::StopCrouching(const FInputActionValue& Value)
{
	ServerStopCrouching();
	//if (bIsCrouching)
	//{
		//bIsCrouching = false;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("StopCrouch!")));
		//GetCapsuleComponent()->SetCapsuleHalfHeight(OriginalCapsuleHalfHeight);
		//GetCapsuleComponent()->SetRelativeLocation(OriginalCapsuleLocation);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("falseline")));
	//}

}



//Sprint
void AAJ_Character::Sprint(const FInputActionValue& Value)
{
	ServerSprint();

	//bIsSprintKeyPressed = true;

	//APlayerController* PlayerController = Cast<APlayerController>(GetController());
	//if (PlayerController)
	//{
	//	APlayerPlayerState* PlayerPlayerState = Cast<APlayerPlayerState>(PlayerController->PlayerState);
	//	if (PlayerPlayerState)
	//	{
	//		float VSTM = PlayerPlayerState->m_CurSTM;

	//		if (bIsSprintKeyPressed && !bIsSprint && VSTM < 150)
	//		{
	//			bIsSprint = true;
	//			GetCharacterMovement()->MaxWalkSpeed = AJDefaultWalkSpeed * SprintSpeedMultiplier;

	//			GetWorldTimerManager().SetTimer(STMDTimerHandle, this, &AAJ_Character::STMDTimer, 0.1f, true);
	//			GetWorldTimerManager().ClearTimer(STMUTimerHandle);

	//		}
	//	}
	//}
}


void AAJ_Character::StopSprint(const FInputActionValue& Value)
{
	ServerStopSprint();
	//bIsSprintKeyPressed = false;

	//if (bIsSprint)
	//{
	//	bIsSprint = false;
	//	GetCharacterMovement()->MaxWalkSpeed = AJDefaultWalkSpeed;
	//}
	//GetWorldTimerManager().ClearTimer(STMDTimerHandle);
	//GetWorldTimerManager().SetTimer(STMUTimerHandle, this, &AAJ_Character::STMUTimer, 0.1f, true);
}

//Parkour
void AAJ_Character::Parkour(const FInputActionValue& Value)
{
	ServerParkour();
}

// Dead
void AAJ_Character::Dead()
{

	APlayerPlayerState* ps = Cast<APlayerPlayerState>(GetPlayerState());
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%s"),ps));
	if (IsValid(ps))
	{
		ps->m_Dele_UpdateHp.AddDynamic(this, &AAJ_Character::ServerDead);
	}
	else
	{
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.SetTimer(th_looping, this, &AAJ_Character::Dead, 0.1f, true);
	}

}


//Reload
void AAJ_Character::Reload(const FInputActionValue& Value)
{
	ServerReload();
}

// Trigger
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
void AAJ_Character::STMDTimer()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		APlayerPlayerState* PlayerPlayerState = Cast<APlayerPlayerState>(PlayerController->PlayerState);
		if (PlayerPlayerState)
		{
			PlayerPlayerState->AddSTM();

			float VSTM = PlayerPlayerState->m_CurSTM;

			if (bIsSprint && VSTM >= 150)
			{
				bIsSprint = false;
				GetCharacterMovement()->MaxWalkSpeed = AJDefaultWalkSpeed;

				GetWorldTimerManager().ClearTimer(STMDTimerHandle);
				GetWorldTimerManager().SetTimer(STMUTimerHandle, this, &AAJ_Character::STMUTimer, 0.1f, true);
			}
		}
	}
}
void AAJ_Character::STMUTimer()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		APlayerPlayerState* PlayerPlayerState = Cast<APlayerPlayerState>(PlayerController->PlayerState);
		if (PlayerPlayerState)
		{

			PlayerPlayerState->UseSTM();

		}
	}
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

	IWeaponInterface* WeaponData_Multi = Cast<IWeaponInterface>(GetClass());
	if (WeaponClass_Save)
	{
		WeaponData_Multi->Execute_WeaponShoot(WeaponClass_Save);
	}


	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("WeaponData Null")));
}
//Parkour
void AAJ_Character::ServerParkour_Implementation()
{
	MultiParkour();
}
void AAJ_Character::MultiParkour_Implementation()
{
	if (!bIsParkour)
	{
		bIsParkour = true;

		// 트레이스 시작 위치 설정
		FVector StartLocation = GetActorLocation();

		// 수평 방향으로 라인 트레이스 수행
		FVector ForwardVector = GetActorForwardVector();
		FVector EndLocation = StartLocation + ForwardVector * TraceDistance;

		// 트레이스 파라미터 설정
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		// 히트 결과를 저장할 구조체
		FHitResult HitResult;

		// 수평 방향으로 라인 트레이스 수행
		bool bHitHorizontal = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECC_Visibility,
			CollisionParams
		);

		// 수직 방향으로 라인 트레이스 수행
		FVector VerticalEndLocation = StartLocation + FVector(0, 0, -TraceDistance); // 수직 방향으로 트레이스
		bool bHitVertical = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			VerticalEndLocation,
			ECC_Visibility,
			CollisionParams
		);

		DrawDebugLine(GetWorld(), StartLocation, VerticalEndLocation, FColor::Green, false, -1, 0, 1.0f);

		// 히트한 경우 처리
		if (bHitHorizontal && bHitVertical)
		{
			// 히트한 액터에 대한 추가 작업 수행
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				// 여기에서 원하는 작업을 수행하세요.
				// 높이 정보는 HitResult.ImpactPoint.Z 등을 통해 얻을 수 있습니다.
				float Height = HitResult.ImpactPoint.Z - StartLocation.Z;
			}
		}

		// 디버그 레이를 그리기 위한 코드 (원하는 경우 사용)
		if (bDrawDebugLine)
		{
			DrawDebugLine(
				GetWorld(),
				StartLocation,
				EndLocation,
				FColor::Green,
				false, -1, 0,
				1.0f
			);

			DrawDebugLine(
				GetWorld(),
				StartLocation,
				VerticalEndLocation,
				FColor::Blue,
				false, -1, 0,
				1.0f
			);
		}
	}
	else
	{
		bIsParkour = false;
	}
	GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
	GetWorldTimerManager().SetTimer(ParkourTimerHandle, this, &AAJ_Character::ParkourTimer, 1.0f, false);
	//캡슐을 전방으로 1M이동하게 만드세요.
	//GetCapsuleComponent()->GetForwardVector();
	// 

	FVector ForwardVector = GetCapsuleComponent()->GetForwardVector();
	float ForwardX = ForwardVector.X * 100;
	FVector MovePosion(ForwardX, 0, 0);
	GetCapsuleComponent()->AddRelativeLocation(MovePosion);// 전방 벡터를 이용하여 플레이어 캐릭터를 앞으로 이동시키기

	//GetWorldTimerManager().SetTimer(ParkourAnimation, this, &AAJ_Character::animationTimer, 0.1f, bLessIsDistnace);


	//float MovementSpeed = 100.0f; // 이동 속도 설정 (원하는 값으로 변경)
	//AddMovementInput(ForwardVector, MovementSpeed);

}

void AAJ_Character::ServerStartCrouch_Implementation()
{
	MultiStartCrouch();
}

void AAJ_Character::ServerStopCrouching_Implementation()
{
	MultiStopCrouching();
}

void AAJ_Character::MultiStartCrouch_Implementation()
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("StartCrouch!")));
	}
}

void AAJ_Character::MultiStopCrouching_Implementation()
{
	if (bIsCrouching)
	{
		bIsCrouching = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("StopCrouch!")));
		//GetCapsuleComponent()->SetCapsuleHalfHeight(OriginalCapsuleHalfHeight);
		//GetCapsuleComponent()->SetRelativeLocation(OriginalCapsuleLocation);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("falseline")));
	}
}

//Sprint
void AAJ_Character::ServerSprint_Implementation()
{
	MultiSprint();
}

void AAJ_Character::ServerStopSprint_Implementation()
{
	MultiStopSprint();
}

void AAJ_Character::MultiSprint_Implementation()
{
	bIsSprintKeyPressed = true;

	if (!bIsSprint)
	{
		bIsSprint = true;

		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			APlayerPlayerState* PlayerPlayerState = Cast<APlayerPlayerState>(PlayerController->PlayerState);
			if (PlayerPlayerState)
			{
				float VSTM = PlayerPlayerState->m_CurSTM;

				if (bIsSprintKeyPressed && !bIsSprint && VSTM < 150)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("StartSprint!")));

					GetCharacterMovement()->MaxWalkSpeed = AJDefaultWalkSpeed * SprintSpeedMultiplier;

					GetWorldTimerManager().SetTimer(STMDTimerHandle, this, &AAJ_Character::STMDTimer, 0.1f, true);
					GetWorldTimerManager().ClearTimer(STMUTimerHandle);

				}
			}
		}
	}
	
	
}

void AAJ_Character::MultiStopSprint_Implementation()
{
	bIsSprintKeyPressed = false;

	if (bIsSprint)
	{
		bIsSprint = false;
		GetCharacterMovement()->MaxWalkSpeed = AJDefaultWalkSpeed;
	}
	GetWorldTimerManager().ClearTimer(STMDTimerHandle);
	GetWorldTimerManager().SetTimer(STMUTimerHandle, this, &AAJ_Character::STMUTimer, 0.1f, true);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("StopSprint!")));
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
		//AAmmoBase* ammoClass = Cast<AAmmoBase>(WeaponClass);
		WeaponData->Execute_SettingOwner(WeaponClass_Save, this);
		//WeaponData->OwnedCharacter = this;
		if (bIsEquiped == true)
		{
			bIsEquiped = false;
			WeaponData->Execute_DropWeapon(WeaponClass_Save);
			WeaponData = nullptr;
		}
		else
		{
			//무기를 들고있을 경우 drop처리
			WeaponData->Execute_EquipWeapon(WeaponClass_Save);
			bIsEquiped = true;
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("MultiInteraction_Implementation")));
}

//Dead
void AAJ_Character::ServerDead_Implementation(float CurHp, float MaxHp, int CurHpText)
{
	MultiDead(CurHp, MaxHp, CurHpText);

}

void AAJ_Character::MultiDead_Implementation(float CurHp, float MaxHp, int CurHpText)
{
	if (CurHp <= 0)
	{
		if (!bIsDead)
		{
			bIsDead = true;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("MultiDead_Implementation")));
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			USkeletalMeshComponent* MeshComp = GetMesh();
			if (MeshComp)
			{
				MeshComp->SetCollisionProfileName(TEXT("Ragdoll"));
				MeshComp->SetSimulatePhysics(true);
			}
		}
	}
}


void AAJ_Character::OnWeaponBeingOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Name %s"), *OtherActor->GetClass()->GetName()));

	WeaponClass = Cast<AWeaponBase>(OtherActor);
	WeaponData = Cast<IWeaponInterface>(OtherActor);
	AmmoBase = Cast<AAmmoBase>(OtherActor);
	if(AmmoBase)
	{	
		
		float Damage= 10;

		EBulletType Type = EBulletType::AR_5;
		switch (Type)
		{
		case EBulletType::AR_5: 
			Damage = 10;
			break;
		case EBulletType::AR_7:
			Damage = 20;
			break;
		case EBulletType::AR_9:
			Damage = 8;
			break;
		}
		
		TObjectPtr<ACharacter> ConvertCharacter = this;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);//트레이스채널로 다시체크?
		WeaponData->Execute_Hit(AmmoBase, GetWorld()->GetFirstPlayerController());

		APlayerPlayerState* PS = Cast<APlayerPlayerState>(GetPlayerState());
		if (PS)
		{

			PS->AddDamage(Damage);
			/*	PS->AddDamage_Text(Damage);*/
		}


		AmmoBase->K2_DestroyActor();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("%f"),HP));
	}
	SaveVariable(OtherActor);
	//UE_LOG����
	//UE_LOG(LogTemp, Warning, TEXT("Current values are: vector %s, float %f, and integer %d"), *ExampleVector.ToString(), ExampleFloat, ExampleInteger);

}

void AAJ_Character::OnWeaponEndOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (WeaponClass)
	{
		if (WeaponData != nullptr)
		{
			//WeaponData->Execute_ClearOwner(WeaponClass);
		}
	}
	else if (AmmoBase)
	{
		if (IsValid(AmmoBase))
		{
			AmmoBase->K2_DestroyActor();
		}

	}
}

void AAJ_Character::SaveVariable(AActor* OtherActor)
{
	if (OtherActor == WeaponClass)
	{
		WeaponClass_Save = Cast<AWeaponBase>(OtherActor);

	}
}

void AAJ_Character::ResetCameraRotation()
{
	// 여기에 카메라 회전을 초기 상태로 되돌리는 로직을 추가
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		FRotator NewRotation = GetActorRotation();
		PlayerController->SetControlRotation(NewRotation);
	}
}

void AAJ_Character::ParkourTimer()
{
	GetCapsuleComponent()->SetCollisionProfileName("Pawn");
}

void AAJ_Character::animationTimer()
{

}


