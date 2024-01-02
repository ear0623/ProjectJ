// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "SStatWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECTJ_API USStatWidget : public UWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(BindWidget))
	TObjectPtr<UButton> SampleButton;

protected:
	
};
