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

	// �X�R�A�擾
	UFUNCTION()
		int GetScore() { return CurrentScore; }

	// �X�R�A���Z
	UFUNCTION()
		void AddScore(int Value) { CurrentScore += Value; }

private:

	UPROPERTY()
		int CurrentScore;
};
