// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayModeWidget.generated.h"

class AScoreState;
class UTextBlock;

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

	UPROPERTY(EditAnywhere)
		UTextBlock* ScoreText;

	UPROPERTY()
		AScoreState* ScoreState;

protected:
	// Called when the game starts or when spawned
	virtual void NativeConstruct() override;
};
