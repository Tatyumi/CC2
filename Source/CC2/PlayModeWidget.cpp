// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayModeWidget.h"
#include "Components/TextBlock.h"
#include "ScoreState.h"

UPlayModeWidget::UPlayModeWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
}

void UPlayModeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ���[���h����AScoreState���擾
	ScoreState = GetWorld() != NULL ? GetWorld()->GetGameState<AScoreState>() : NULL;

	DisplayScore();
}

// �X�R�A�\��
void UPlayModeWidget::DisplayScore()
{
	if (ScoreText == nullptr &&ScoreState == nullptr)
	{
		return;
	}

	ScoreText->SetText(FText::AsNumber(ScoreState->GetScore()));
}

// ���Z��̃X�R�A�\��
void UPlayModeWidget::DisplayAddScore(int Value)
{
	if (ScoreText == nullptr &&ScoreState == nullptr)
	{
		return;
	}

	// �X�R�A���Z
	ScoreState->AddScore(Value);

	ScoreText->SetText(FText::AsNumber(ScoreState->GetScore()));
}