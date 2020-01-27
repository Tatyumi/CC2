// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayModeWidget.h"
#include "ScoreState.h"

#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

UPlayModeWidget::UPlayModeWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
}

void UPlayModeWidget::NativeConstruct()
{
	Super::NativeConstruct();


	// ワールドからAScoreStateを取得
	ScoreState = GetWorld() != NULL ? GetWorld()->GetGameState<AScoreState>() : NULL;

	DisplayScore();

	if (MessagePnl)
	{
		// メッセージパネルを非表示
		MessagePnl->SetVisibility(ESlateVisibility::Collapsed);
	}

	DispTime = 4.0f;
	DeltaTime = 0.0f;
}

void UPlayModeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// メッセージパネルが表示されているか判別
	if (MessagePnl->Visibility == ESlateVisibility::Visible)
	{
		DeltaTime += InDeltaTime;

		// 一定時間経過したか判別
		if (DeltaTime >= DispTime)
		{
			// メッセージパネルを非表示
			MessagePnl->SetVisibility(ESlateVisibility::Collapsed);
			DeltaTime = 0.0f;
		}
	}
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

// メッセージパネルの表示
void UPlayModeWidget::DispMessagePnl()
{
	MessagePnl->SetVisibility(ESlateVisibility::Visible);
}