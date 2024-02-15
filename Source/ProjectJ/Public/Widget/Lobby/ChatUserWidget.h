// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatUserWidget.generated.h"


class UTextBlock;
class UScrollBox;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class PROJECTJ_API UChatUserWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	void UpatePlayerCount(int32 InPlayerCount);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerCountTextBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI", meta = (BindWidget))
	TObjectPtr<UScrollBox> ChatScrollBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI", meta = (BindWidget))
	TObjectPtr<UEditableTextBox> ChatInputTextBox;


	UFUNCTION()
	void ProcessChanged(const FText& Text);

	UFUNCTION()
	void ProcessCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION(BlueprintCallable)
	void AddMessage(const FString& InMessge);
};
