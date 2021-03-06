// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputModeSetable.h"
#include "Blueprint/UserWidget.h"
#include "TitleUserWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class CC2_API UTitleUserWidget : public UUserWidget, public IInputModeSetable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UTextBlock* GuideTxt;

protected:
	// Called when the game starts or when spawned
	virtual void NativeConstruct() override;

	// キー入力
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)override;

public:

	// 入力に関するを行う
	virtual void SetInputSetting()override;
};