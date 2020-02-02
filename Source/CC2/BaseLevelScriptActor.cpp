// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelScriptActor.h"
#include "StartPoint.h"
#include "GoalPoint.h"
#include "CC2GameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// イベントポイントの座標
static const FVector EVENT_POINT_POS = FVector(-810.0f, 10.0f, 110.0f);

void ABaseLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	ACC2GameModeBase* gameMode = Cast<ACC2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (SubWidget != nullptr)
	{
		// ウィジットを生成
		Widget = CreateWidget<UUserWidget>(GetWorld(), SubWidget);

		if (Widget != nullptr)
		{
			// ウィジットを表示
			Widget->AddToViewport();

			if (gameMode)
			{
				// 現在表示しているウィジットを取得
				gameMode->SetCurrentWidget(Widget);
			}
		}
	}

	if (SubStartPoint)
	{
		// スタートポイントを生成
		StartPoint = GetWorld()->SpawnActor<AStartPoint>(SubStartPoint, EVENT_POINT_POS, FRotator::ZeroRotator);

		if (StartPoint)
		{
			StartPoint->SetActorEnableCollision(true);

			if (gameMode)
			{
				// スタート地点の取得
				gameMode->SetEventPoint(StartPoint);
			}
		}
	}

	if (SubGoalPoint)
	{
		// ゴールポイントを生成
		GoalPoint = GetWorld()->SpawnActor<AGoalPoint>(SubGoalPoint, EVENT_POINT_POS, FRotator::ZeroRotator);
		if (GoalPoint)
		{
			// ゴール地点の取得
			gameMode->SetEventPoint(GoalPoint);
		}
	}
}