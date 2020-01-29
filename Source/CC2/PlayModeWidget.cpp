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


	// ワールドからAScoreStateを取得
	ScoreState = GetWorld() != NULL ? GetWorld()->GetGameState<AScoreState>() : NULL;

	DisplayScore();

	if (MessagePnl)
	{
		// メッセージパネルを非表示
		MessagePnl->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (GameClearPnl)
	{
		// ゲームクリアパネルを非表示
		GameClearPnl->SetVisibility(ESlateVisibility::Collapsed);
	}
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

	// ゲームクリアパネルが表示されているか判別
	if (GameClearPnl->Visibility == ESlateVisibility::Visible)
	{
		DeltaTime += InDeltaTime;

		// 一定時間経過したか判別
		if (DeltaTime >= ClaredWaitTime)
		{
			// 次のシーンに遷移する
			ULevelMover* levelMover = NewObject<ULevelMover>();
			// TODO 次のレベルを指定する仕組みを作る
			levelMover->MoveLevel(GetWorld(),0);
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

// ゲームクリアパネルを表示
void UPlayModeWidget::DispGameClearPnl()
{
	GameClearPnl->SetVisibility(ESlateVisibility::Visible);
}