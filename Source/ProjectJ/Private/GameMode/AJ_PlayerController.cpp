// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/AJ_PlayerController.h"
#include "EnhancedInputSubsystems.h" // 향상된 입력을 사용하기 위해 선언

void AAJ_PlayerController::BeginPlay()
{
	Super::BeginPlay(); //super -

	// ULocalPlayer 클래스로의 서브시스템을 가져와서 이곳에서 현재 로컬플레이어 정보를 가져옵니다
	UEnhancedInputLocalPlayerSubsystem* SubSystem =ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	// 서브시스템이 유효하고, DefaultIMC 가 유효한 경우 로직을 이어간다
	if (SubSystem && DefaultIMC)
		// MappingContext 인 DefaultIMC 를 서브 시스템에 추가, 0은 컨텍스트의 우선순위
		SubSystem->AddMappingContext(DefaultIMC, 0);
}


