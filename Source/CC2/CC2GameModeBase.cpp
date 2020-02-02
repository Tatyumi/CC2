// Fill out your copyright notice in the Description page of Project Settings.


#include "CC2GameModeBase.h"
#include "BasePlayer.h"

#include "Blueprint/UserWidget.h"

ACC2GameModeBase::ACC2GameModeBase()
{
	DefaultPawnClass = ABasePlayer::StaticClass();
}

// イベントポイントのコリジョン切り替え
void ACC2GameModeBase::SwitchEventPoints()
{
	for (auto eventPoint : EventPoints)
	{
		AActor* actor = Cast<AActor>(eventPoint);
		actor->SetActorEnableCollision(!actor->GetActorEnableCollision());
	}
}