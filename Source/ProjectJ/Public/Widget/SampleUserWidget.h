// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SampleUserWidget.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class PROJECTJ_API USampleUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> SampleButton;
};
