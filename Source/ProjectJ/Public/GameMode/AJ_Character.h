// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" // InputAction 
#include "WeaponInterface.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"  // AISense_Sight 헤더 파일 추가

#include "AJ_Character.generated.h"

//DECLARE_MULTICAST_DELEGATE_OneParam(FDele_Update)

class USpringArmComponent; //SpringArmComponent
class UCameraComponent; // CameraComponent
class UInputAction;// InputAction
struct FInputActionValue;//InputActionValue
class UAnimMontage;//AnimMontage
class AWeaponBase; // AWeaponBase
class IWeaponInterface;
class AAmmoBase;


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
	//Parkour
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InPut", meta = (AllowprivateAccess = "true"))
	UInputAction* IA_Parkour;


	////////////�Է�Ű �Լ� ����///////////////////////////////////////////////////////////////////////////
	
	
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
	UFUNCTION()
	void Sprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	//Parkour
	void Parkour(const FInputActionValue& Value);
	//Dead
	void Dead(const FInputActionValue& Value);
	

private:
	//IsSprint?
	bool bIsSprintKeyPressed;


/////////////////////////////Network/////////////////////////////////////////////////////////////////
public:

	//Trigger
	UFUNCTION(Server, Reliable)
	void ServerTrigger();
	UFUNCTION(NetMulticast, Reliable)
	void MultiTrigger();

	void MultiTrigger_Implementation();

	void MultiParkour_Implementation();
	
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

	//Parkour
	UFUNCTION(Server, Reliable)
	void ServerParkour();
	UFUNCTION(NetMulticast, Reliable)
	void MultiParkour();

	//Dead
	UFUNCTION(Server, Reliable)
	void ServerDead();
	UFUNCTION(NetMulticast, Reliable)
	void MultiDead();
/////////////////////////////Deligate/////////////////////////////////////////////////////////////////

//////////////////////////////////Animontage/////////////////////////////////////////////////////////////////////
	

public:
	// Trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage>TriggerMontage;


	// Reload
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ReloadMontage;

	//////////////////////////////////Actor///////////////////////////////////////////////////////////////////
public:
	UFUNCTION()
	void OnWeaponBeingOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponEndOverap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	IWeaponInterface* WeaponData;

	TObjectPtr<AWeaponBase> WeaponClass;

	void SaveVariable(AActor* OtherActor);

	TObjectPtr<AWeaponBase> WeaponClass_Save;


	///////////////////////Variables//////////////////

	
public:
	//Crouch varuables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool bIsCrouching;

	//Equip variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool bIsEquiped;

	//Sprint variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool bIsSprint; //Sprint variabel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float AJDefaultWalkSpeed; //CharacterDefaultWalkSpeed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float SprintSpeedMultiplier; //Sprint Speed
	
	//Parkour variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float TraceDistance = 10.0f; //ParkourLinTrace
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool bDrawDebugLine = true;//LineTraceDebugLine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool bIsParkour; //Parkour variables
	//Dead
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool bIsDead; //Dead variables
	
	//HP
	float HP;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	TObjectPtr<AAmmoBase> AmmoBase;

	//Parkour
	void ResetCameraRotation();


public:



	void STMDTimer();
	void STMUTimer();

	FTimerHandle STMDTimerHandle;
	FTimerHandle STMUTimerHandle;
	FTimerHandle ParkourTimerHandle;

	void ParkourTimer();

	FTimerHandle ParkourAnimation;

	void animationTimer();

public:

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionStimuliSourceComponent* StimuliSourceComponent;

};	
