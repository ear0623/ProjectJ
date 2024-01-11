// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" //��ǲ�׼��� ����ϱ� ���� �ݵ�� �� ��ġ�� �ִ´�.
#include "WeaponInterface.h"
#include "AJ_Character.generated.h"

DECLARE_DELEGATE(FDele_UpdateShoot);

// ���� ���� 
class USpringArmComponent; //�������� ����� ���� ����
class UCameraComponent; //ī�޶� ����� ���� ����
class UInputAction;//
struct FInputActionValue;//
class UAnimMontage;//�ִԸ�Ÿ�� ����� ���� ����

UCLASS()
class PROJECTJ_API AAJ_Character : public ACharacter
{
	GENERATED_BODY()

	/////////////ī�޶� ���� �߰�////////////////////////////////

	//��������
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	//ī�޶�
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	//////////////////////////////////�Է�Ű ����//////////////////////////////////////////////////////////////

	//����
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Jump;
	//����
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Move;
	//��
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Look;
	//�ɱ� 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Crouch;
	//������
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Reload;
	//����
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Shoot;

	////////////�Է�Ű �Լ� ����///////////////////////////////////////////////////////////////////////////
	
	//������ �̹� �⺻���ÿ� �ֱ� ������ �߰� ������
	
	//����
	void Move(const FInputActionValue& Value);
	//��
	void Look(const FInputActionValue& Value);
	//�ɱ�
	void Crouch(const FInputActionValue& Value);
	void StopCrouching(const FInputActionValue& Value);
	//������
	void Reload(const FInputActionValue& Value);
	//����
	void Shoot(const FInputActionValue& Value);


/////////////////////////////��Ʈ��ũ  �ڵ� ����/////////////////////////////////////////////////////////////////
public:
	//�ɱ�
	UFUNCTION(Server, Reliable)
	void ServerCrouch();
	UFUNCTION(NetMulticast, Reliable)
	void MultiCrouch();


	//����
	UFUNCTION(Server, Reliable)
	void ServerShoot();
	UFUNCTION(NetMulticast, Reliable)
	void MultiShoot();
	
	//������
	UFUNCTION(Server, Reliable)
	void ServerReload();
	UFUNCTION(NetMulticast, Reliable)
	void MultiReload();


//////////////////////////////////�ִԸ�Ÿ��/////////////////////////////////////////////////////////////////////
public:
	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ShootMontage;

	//�ɱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> CrouchMontage;

	//������
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
