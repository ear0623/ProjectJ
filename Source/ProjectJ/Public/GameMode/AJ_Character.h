// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" //��ǲ�׼��� ����ϱ� ���� �ݵ�� �� ��ġ�� �ִ´�.
#include "AJ_Character.generated.h"


// ���� ���� 
class USpringArmComponent; //�������� ����� ���� ����
class UCameraComponent; //ī�޶� ����� ���� ����
class UInputAction;//
struct FInputActionValue;//
class UAnimMontage;//�ִԸ�Ÿ�� ����� ���� ����
class AWeaponBase;


UCLASS()
class PROJECTJ_API AAJ_Character : public ACharacter
{
	GENERATED_BODY()


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
	UInputAction* IA_Trigger;
	//��ȣ�ۿ�
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Interaction;
	//�޸���
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowprivateAccess = "true"))
	UInputAction* IA_Sprint;

	////////////�Է�Ű �Լ� ����///////////////////////////////////////////////////////////////////////////
	
	//������ �̹� �⺻���ÿ� �ֱ� ������ �߰� ������
	
	//����
	void Move(const FInputActionValue& Value);
	//��
	void Look(const FInputActionValue& Value);
	//�ɱ�
	void StartCrouch(const FInputActionValue& Value);
	void StopCrouching(const FInputActionValue& Value);
	bool bIsCrouching;
	// ����ĸ��������Ʈ�� ���� ����, ��ġ�� ����
	FVector OriginalCapsuleLocation;
	float OriginalCapsuleHalfHeight;
	//������
	void Reload(const FInputActionValue& Value);
	//����
	void Trigger(const FInputActionValue& Value);
	//��ȣ�ۿ�
	void Interaction(const FInputActionValue& Value);
	//�޸���
	void Sprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	float SprintSpeedMultiplier;


/////////////////////////////��Ʈ��ũ  �ڵ� ����/////////////////////////////////////////////////////////////////
public:
	//�ɱ� //movement��� �̸��� ���� ������Ʈ�� Replicated�� �����Ǿ��ִ�.
	//UFUNCTION(Server, Reliable)
	//void ServerCrouch();
	//UFUNCTION(NetMulticast, Reliable)
	//void MultiCrouch();

	//����
	UFUNCTION(Server, Reliable)
	void ServerTrigger();
	UFUNCTION(NetMulticast, Reliable)
	void MultiTrigger();

	void MultiTrigger_Implementation();
	
	//������
	UFUNCTION(Server, Reliable)
	void ServerReload();
	UFUNCTION(NetMulticast, Reliable)
	void MultiReload();

	//��ȣ�ۿ�
	UFUNCTION(Server, Reliable)
	void ServerInteraction();
	UFUNCTION(NetMulticast, Reliable)
	void MultiInteraction();
/////////////////////////////Deligate/////////////////////////////////////////////////////////////////

	
//////////////////////////////////�ִԸ�Ÿ��/////////////////////////////////////////////////////////////////////
public:
	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage>TriggerMontage;

	//�ɱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> CrouchMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> StopCrouchMontage;

	//������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ReloadMontage;

	//�޸���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> SprintMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> StopSprintMontage;


	//////////////////////////////////���Ͱ���///////////////////////////////////////////////////////////////////

protected:
	UFUNCTION()
	void OnWeaponBeingOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponEndOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TObjectPtr<AWeaponBase> Weapon;

	bool bIsEquiped;
};	
