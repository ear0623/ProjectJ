// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/AJ_PlayerController.h"
#include "EnhancedInputSubsystems.h" // ���� �Է��� ����ϱ� ���� ����

void AAJ_PlayerController::BeginPlay()
{
	Super::BeginPlay(); //super -

	// ULocalPlayer Ŭ�������� ����ý����� �����ͼ� �̰����� ���� �����÷��̾� ������ �����ɴϴ�
	UEnhancedInputLocalPlayerSubsystem* SubSystem =ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	// ����ý����� ��ȿ�ϰ�, DefaultIMC �� ��ȿ�� ��� ������ �̾��
	if (SubSystem && DefaultIMC)
		// MappingContext �� DefaultIMC �� ���� �ý��ۿ� �߰�, 0�� ���ؽ�Ʈ�� �켱����
		SubSystem->AddMappingContext(DefaultIMC, 0);
}


