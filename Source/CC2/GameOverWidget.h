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

	// �^�C�g���ɖ߂�{�^��
	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UButton* TitleBackBtn;

	// ���X�^�[�g�{�^��
	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UButton* ReStartBtn;

private:

	// �^�C�g����ʂɑJ��
	UFUNCTION()
		void MoveTitle();

	// �ĊJ
	UFUNCTION()
		void ReStart();
};