// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AJ_PlayerController.generated.h"

class UInputMappingContext; //���� ����

/**
 * 
 */
UCLASS()
class PROJECTJ_API AAJ_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Ŀ���� InputMappingContext �� ����ϱ� ���� ����(�Ӽ�)�� �߰�
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")
	TObjectPtr<UInputMappingContext> DefaultIMC;

	virtual void BeginPlay() override; // BeginPlay�� ���� ���ε� �ϱ�� ����

};
