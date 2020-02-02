// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyItem.h"
#include "PlayModeWidget.h"
#include "CC2GameModeBase.h"
#include "BaseLevelScriptActor.h"
#include "EventOccurable.h"

#include "Kismet/GameplayStatics.h"

// アイテムスコア
static const int KEY_ITEM_SCORE = 1000;

AKeyItem::AKeyItem() : ABaseItem(KEY_ITEM_SCORE)
{
}


// アイテム取得処理
void AKeyItem::Pickedup()
{
	ACC2GameModeBase* gameMode = Cast<ACC2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (gameMode == nullptr)
	{
		return;
	}

	// イベントポイントの切り替え
	gameMode->SwitchEventPoints();

	UPlayModeWidget* PlayModeWidget = Cast<UPlayModeWidget>(gameMode->GetCurrentWidget());

	if (PlayModeWidget == nullptr)
	{
		return;
	}

	// スコア加算処理
	PlayModeWidget->DisplayAddScore(Score);
	Destroy(this);
}