// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayModeWidget.h"
#include "ScoreState.h"
#include "LevelMover.h"

#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

UPlayModeWidget::UPlayModeWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	DispTime = 4.0f;
	DeltaTime = 0.0f;
	ClaredWaitTime = 5.0f;
}

void UPlayModeWidget::NativeConstruct()
{
	Super::NativeConstruct();


	// ���[���h����AScoreState���擾
	ScoreState = GetWorld() != NULL ? GetWorld()->GetGameState<AScoreState>() : NULL;

	DisplayScore();

	if (MessagePnl)
	{
		// ���b�Z�[�W�p�l�����\��
		MessagePnl->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (GameClearPnl)
	{
		// �Q�[���N���A�p�l�����\��
		GameClearPnl->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UPlayModeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// ���b�Z�[�W�p�l�����\������Ă��邩����
	if (MessagePnl->Visibility == ESlateVisibility::Visible)
	{
		DeltaTime += InDeltaTime;

		// ��莞�Ԍo�߂���������
		if (DeltaTime >= DispTime)
		{
			// ���b�Z�[�W�p�l�����\��
			MessagePnl->SetVisibility(ESlateVisibility::Collapsed);
			DeltaTime = 0.0f;
		}
	}

	// �Q�[���N���A�p�l�����\������Ă��邩����
	if (GameClearPnl->Visibility == ESlateVisibility::Visible)
	{
		DeltaTime += InDeltaTime;

		// ��莞�Ԍo�߂���������
		if (DeltaTime >= ClaredWaitTime)
		{
			// ���̃V�[���ɑJ�ڂ���
			ULevelMover* levelMover = NewObject<ULevelMover>();
			// TODO ���̃��x�����w�肷��d�g�݂����
			levelMover->MoveLevel(GetWorld(),0);
		}
	}
}

// �X�R�A�\��
void UPlayModeWidget::DisplayScore()
{
	if (ScoreTxt == nullptr || ScoreState == nullptr)
	{
		return;
	}

	ScoreTxt->SetText(FText::AsNumber(ScoreState->GetScore()));
}

// ���Z��̃X�R�A�\��
void UPlayModeWidget::DisplayAddScore(int Value)
{
	if (ScoreTxt == nullptr || ScoreState == nullptr)
	{
		return;
	}

	// �X�R�A���Z
	ScoreState->AddScore(Value);

	ScoreTxt->SetText(FText::AsNumber(ScoreState->GetScore()));
}

// ���b�Z�[�W�p�l���̕\��
void UPlayModeWidget::DispMessagePnl()
{
	MessagePnl->SetVisibility(ESlateVisibility::Visible);
}

// �Q�[���N���A�p�l����\��
void UPlayModeWidget::DispGameClearPnl()
{
	GameClearPnl->SetVisibility(ESlateVisibility::Visible);
}