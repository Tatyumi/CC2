// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ScoreState.generated.h"

UCLASS()
class CC2_API AScoreState : public AGameStateBase
{
	GENERATED_BODY()

public:

	AScoreState();

	// スコア取得
	UFUNCTION()
		int GetScore()const { return CurrentScore; }

	// スコア加算
	UFUNCTION()
		void AddScore(int Value) { CurrentScore += Value; }

private:

	// 現在のスコア
	UPROPERTY()
		uint32 CurrentScore;
};
