// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayModeWidget.generated.h"

class AScoreState;
class UTextBlock;
class UCanvasPanel;

UCLASS()
class CC2_API UPlayModeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPlayModeWidget(const FObjectInitializer& ObjectInitializer);

	// �X�R�A�\��
	UFUNCTION()
		void DisplayScore();

	// ���Z��̃X�R�A�\��
	UFUNCTION()
		void DisplayAddScore(int Value);

	// ���b�Z�[�W�p�l���̕\��
	UFUNCTION()
		void DispMessagePnl();

	// ���b�Z�[�W�p�l���̕\��
	UFUNCTION()
		void DispGameClearPnl();

public:

	// ���b�Z�[�W�\���p�p�l��
	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UCanvasPanel* MessagePnl;

	// �Q�[���N���A�p�l��
	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UCanvasPanel* GameClearPnl;

	// �X�R�A�e�L�X�g
	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UTextBlock* ScoreTxt;

	// �X�R�A�I�u�W�F�N�g
	UPROPERTY()
		AScoreState* ScoreState;

protected:
	// Called when the game starts or when spawned
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	// �\������
	float DispTime;

	// �o�ߎ���
	float DeltaTime;

	// �N���A��̑ҋ@����
	float ClaredWaitTime;
};
