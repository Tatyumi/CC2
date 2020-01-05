// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayModeWidget.h"

UPlayModeWidget::UPlayModeWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
}

void UPlayModeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ワールドからAScoreStateを取得
	ScoreState = GetWorld() != NULL ? GetWorld()->GetGameState<AScoreState>() : NULL;

	DisplayScore();
}

// スコア表示
void UPlayModeWidget::DisplayScore()
{
	if (ScoreText)
	{
		if (ScoreState)
		{
			ScoreText->SetText(FText::AsNumber(ScoreState->GetScore()));
		}
	}
}

// 加算後のスコア表示
void UPlayModeWidget::DisplayAddScore(int Value)
{
	if (ScoreText)
	{
		if (ScoreState)
		{
			// スコア加算
			ScoreState->AddScore(Value);

			ScoreText->SetText(FText::AsNumber(ScoreState->GetScore()));
		}
	}
}