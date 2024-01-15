// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" //인풋액션을 사용하기 위해 반드시 이 위치에 넣는다.
#include "AJ_Character.generated.h"

DECLARE_DELEGATE(FDele_UpdateShoot);
DECLARE_DELEGATE(FDele_UpdateInteraction);


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
	UInputAction* IA_Trigger;
	//상호작용
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Interaction;
	//달리기
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowprivateAccess = "true"))
	UInputAction* IA_Sprint;

	////////////입력키 함수 설정///////////////////////////////////////////////////////////////////////////
	
	//점프는 이미 기본세팅에 있기 때문에 추가 안해줌
	
	//무브
	void Move(const FInputActionValue& Value);
	//룰
	void Look(const FInputActionValue& Value);
	//앉기
	void StartCrouch(const FInputActionValue& Value);
	void StopCrouching(const FInputActionValue& Value);
	bool bIsCrouching;
	// 원본캡슐컴포넌트의 절반 높이, 위치로 설정
	FVector OriginalCapsuleLocation;
	float OriginalCapsuleHalfHeight;
	//재장전
	void Reload(const FInputActionValue& Value);
	//공격
	void Trigger(const FInputActionValue& Value);
	//상호작용
	void Interaction(const FInputActionValue& Value);
	//달리기
	void Sprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	float SprintSpeedMultiplier;


/////////////////////////////네트워크  코드 영역/////////////////////////////////////////////////////////////////
public:
	//앉기 //movement라고 이름이 붙은 컴포넌트는 Replicated가 설정되어있다.
	//UFUNCTION(Server, Reliable)
	//void ServerCrouch();
	//UFUNCTION(NetMulticast, Reliable)
	//void MultiCrouch();

	//공격
	UFUNCTION(Server, Reliable)
	void ServerTrigger();
	UFUNCTION(NetMulticast, Reliable)
	void MultiTrigger();
	
	//재장전
	UFUNCTION(Server, Reliable)
	void ServerReload();
	UFUNCTION(NetMulticast, Reliable)
	void MultiReload();

	//상호작용
	UFUNCTION(Server, Reliable)
	void ServerInteraction();
	UFUNCTION(NetMulticast, Reliable)
	void MultiInteraction();


//////////////////////////////////애님몽타지/////////////////////////////////////////////////////////////////////
public:
	//공격
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage>TriggerMontage;

	//앉기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> CrouchMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> StopCrouchMontage;

	//재장전
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ReloadMontage;

	//달리기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> SprintMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> StopSprintMontage;


//////////////////////////////////Delgate/////////////////////////////////////////////////////////////////////
private:
	
	FDele_UpdateShoot UpdateTrigger;
	FDele_UpdateInteraction UpdateInteraction;
	

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
