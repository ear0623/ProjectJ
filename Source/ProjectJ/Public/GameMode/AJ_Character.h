// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" // InputAction 
#include "WeaponInterface.h"
#include "AJ_Character.generated.h"

//DECLARE_MULTICAST_DELEGATE_OneParam(FDele_Update)

class USpringArmComponent; //SpringArmComponent
class UCameraComponent; // CameraComponent
class UInputAction;// InputAction
struct FInputActionValue;//InputActionValue
class UAnimMontage;//AnimMontage
class AWeaponBase; // AWeaponBase
class IWeaponInterface;


UCLASS()
class PROJECTJ_API AAJ_Character : public ACharacter , public IWeaponInterface
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


	/////////////CharacterComponent////////////////////////////////

	//SpringArm
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	//Camera
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	//////////////////////////////////Input//////////////////////////////////////////////////////////////

	//Jump
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Jump;
	//Move
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Move;
	//Look
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Look;
	//Crouch 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Crouch;
	//Reload
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Reload;
	//Trigger
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Trigger;
	//Interaction
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Interaction;
	//Sprint
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowprivateAccess = "true"))
	UInputAction* IA_Sprint;

	////////////�Է�Ű �Լ� ����///////////////////////////////////////////////////////////////////////////
	
	//������ �̹� �⺻���ÿ� �ֱ� ������ �߰� ������
	
	// Move
	void Move(const FInputActionValue& Value);
	// Look
	void Look(const FInputActionValue& Value);
	// Crouch
	void StartCrouch(const FInputActionValue& Value);
	void StopCrouching(const FInputActionValue& Value);
	
	// CapsulComponent
	FVector OriginalCapsuleLocation;
	float OriginalCapsuleHalfHeight;
	// Reload
	void Reload(const FInputActionValue& Value);
	// Trigger
	void Trigger(const FInputActionValue& Value);
	// Interaction
	void Interaction(const FInputActionValue& Value);
	// Sprint
	void Sprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	float SprintSpeedMultiplier;


/////////////////////////////Network/////////////////////////////////////////////////////////////////
public:

	//Trigger
	UFUNCTION(Server, Reliable)
	void ServerTrigger();
	UFUNCTION(NetMulticast, Reliable)
	void MultiTrigger();

	void MultiTrigger_Implementation();
	
	//Reload
	UFUNCTION(Server, Reliable)
	void ServerReload();
	UFUNCTION(NetMulticast, Reliable)
	void MultiReload();

	//Interaction
	UFUNCTION(Server, Reliable)
	void ServerInteraction();
	UFUNCTION(NetMulticast, Reliable)
	void MultiInteraction();
/////////////////////////////Deligate/////////////////////////////////////////////////////////////////

//////////////////////////////////Animontage/////////////////////////////////////////////////////////////////////
	

public:
	// Trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage>TriggerMontage;

	// Crouch
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> CrouchMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> StopCrouchMontage;

	// Reload
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ReloadMontage;

	// Sprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> SprintMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> StopSprintMontage;


	//////////////////////////////////Actor///////////////////////////////////////////////////////////////////
protected:
	UFUNCTION()
	void OnWeaponBeingOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponEndOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	IWeaponInterface* WeaponData;

	TObjectPtr<AWeaponBase> WeaponClass;

	//variables bool bIsEquiped
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool bIsEquiped;

	///////////////////////Variables//////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool bIsCrouching;


};	
