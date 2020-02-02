// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UTExtBlock;
class UButton;

UCLASS()
class CC2_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void NativeConstruct() override;

private:

	// タイトルに戻るボタン
	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UButton* TitleBackBtn;

	// リスタートボタン
	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UButton* ReStartBtn;

private:

	// タイトル画面に遷移
	UFUNCTION()
		void MoveTitle();

	// 再開
	UFUNCTION()
		void ReStart();
};