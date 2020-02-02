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

	// スコア表示
	UFUNCTION()
		void DisplayScore();

	// 加算後のスコア表示
	UFUNCTION()
		void DisplayAddScore(int Value);

	// メッセージパネルの表示
	UFUNCTION()
		void DispMessagePnl();

	// メッセージパネルの表示
	UFUNCTION()
		void DispGameClearPnl();

public:

	// メッセージ表示用パネル
	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UCanvasPanel* MessagePnl;

	// ゲームクリアパネル
	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UCanvasPanel* GameClearPnl;

	// スコアテキスト
	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UTextBlock* ScoreTxt;

	// スコアオブジェクト
	UPROPERTY()
		AScoreState* ScoreState;

protected:
	// Called when the game starts or when spawned
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	// 表示時間
	float DispTime;

	// 経過時間
	float DeltaTime;

	// クリア後の待機時間
	float ClaredWaitTime;
};
