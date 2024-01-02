// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" //��ǲ�׼��� ����ϱ� ���� �ݵ�� �� ��ġ�� �ִ´�.
#include "AJ_Character.generated.h"

// ���� ���� 
class USpringArmComponent;
class UCameraComponent;
class UInputAction;

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

	//ī�޶� ���� �߰�
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UCameraComponent> CameraComponent;

	//�Է�Ű ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};	
