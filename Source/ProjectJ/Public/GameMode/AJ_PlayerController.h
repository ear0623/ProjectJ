// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AJ_PlayerController.generated.h"

class UInputMappingContext; //전방 선언

/**
 * 
 */
UCLASS()
class PROJECTJ_API AAJ_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// 커스텀 InputMappingContext 를 사용하기 위해 변수(속성)를 추가
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")
	TObjectPtr<UInputMappingContext> DefaultIMC;

	virtual void BeginPlay() override; // BeginPlay를 동적 바인딩 하기ㅜ 위해

};
