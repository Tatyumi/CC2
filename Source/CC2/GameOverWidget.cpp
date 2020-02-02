// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Components/Button.h"
#include "LevelMover.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (TitleBackBtn)
	{
		TitleBackBtn->OnClicked.AddDynamic(this, &UGameOverWidget::MoveTitle);
	}

	if (ReStartBtn)
	{
		ReStartBtn->OnClicked.AddDynamic(this, &UGameOverWidget::ReStart);
	}
}

// タイトル画面に遷移
void UGameOverWidget::MoveTitle()
{
	ULevelMover* levelMover = NewObject<ULevelMover>();
	levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_TITLE));
}

// 再開
void UGameOverWidget::ReStart()
{

	ULevelMover* levelMover = NewObject<ULevelMover>();
	// TODO死亡したステージを保持する変数から参照するようにする
	levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_STAGE_ONE));
}