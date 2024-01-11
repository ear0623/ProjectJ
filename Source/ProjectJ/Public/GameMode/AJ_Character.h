// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" //인풋액션을 사용하기 위해 반드시 이 위치에 넣는다.
#include "WeaponInterface.h"
#include "AJ_Character.generated.h"

DECLARE_DELEGATE(FDele_UpdateShoot);

// 전방 선언 
class USpringArmComponent; //스프링암 사용을 위해 선언
class UCameraComponent; //카메라 사용을 위해 선언
class UInputAction;//
struct FInputActionValue;//
class UAnimMontage;//애님몽타지 사용을 위해 선언

UCLASS()
class PROJECTJ_API AAJ_Character : public ACharacter
{
	GENERATED_BODY()

	/////////////카메라 변수 추가////////////////////////////////

	//스프링암
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	//카메라
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	//////////////////////////////////입력키 설정//////////////////////////////////////////////////////////////

	//점프
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Jump;
	//무브
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Move;
	//룩
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Look;
	//앉기 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Crouch;
	//재장전
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Reload;
	//공격
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Shoot;

	////////////입력키 함수 설정///////////////////////////////////////////////////////////////////////////
	
	//점프는 이미 기본세팅에 있기 때문에 추가 안해줌
	
	//무브
	void Move(const FInputActionValue& Value);
	//룰
	void Look(const FInputActionValue& Value);
	//앉기
	void Crouch(const FInputActionValue& Value);
	void StopCrouching(const FInputActionValue& Value);
	//재장전
	void Reload(const FInputActionValue& Value);
	//공격
	void Shoot(const FInputActionValue& Value);


/////////////////////////////네트워크  코드 영역/////////////////////////////////////////////////////////////////
public:
	//앉기
	UFUNCTION(Server, Reliable)
	void ServerCrouch();
	UFUNCTION(NetMulticast, Reliable)
	void MultiCrouch();


	//공격
	UFUNCTION(Server, Reliable)
	void ServerShoot();
	UFUNCTION(NetMulticast, Reliable)
	void MultiShoot();
	
	//재장전
	UFUNCTION(Server, Reliable)
	void ServerReload();
	UFUNCTION(NetMulticast, Reliable)
	void MultiReload();


//////////////////////////////////애님몽타지/////////////////////////////////////////////////////////////////////
public:
	//공격
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ShootMontage;

	//앉기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> CrouchMontage;

	//재장전
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ReloadMontage;


//////////////////////////////////Delgate/////////////////////////////////////////////////////////////////////
public:
	
	FDele_UpdateShoot UpdateShoot;
	

public:
	// Sets default values for this character's properties
	AAJ_Character();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;




};	
