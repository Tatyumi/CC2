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

	// ワールドからAScoreStateを取得
	ScoreState = GetWorld() != NULL ? GetWorld()->GetGameState<AScoreState>() : NULL;

	DisplayScore();
}

// スコア表示
void UPlayModeWidget::DisplayScore()
{
	if (ScoreTxt == nullptr || ScoreState == nullptr)
	{
		return;
	}

	ScoreTxt->SetText(FText::AsNumber(ScoreState->GetScore()));
}

// 加算後のスコア表示
void UPlayModeWidget::DisplayAddScore(int Value)
{
	if (ScoreTxt == nullptr || ScoreState == nullptr)
	{
		return;
	}

	// スコア加算
	ScoreState->AddScore(Value);

	ScoreTxt->SetText(FText::AsNumber(ScoreState->GetScore()));
}