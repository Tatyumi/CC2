// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputModeSetable.h"
#include "GameOverWidget.generated.h"

class UTExtBlock;
class UButton;

UCLASS()
class CC2_API UGameOverWidget : public UUserWidget, public IInputModeSetable
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void NativeConstruct() override;

	// キー入力
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)override;

public:

	// 入力に関する設定を行う
	virtual void SetInputSetting()override;
};