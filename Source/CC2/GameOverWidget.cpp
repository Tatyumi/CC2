// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Components/Button.h"
#include "LevelMover.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


// 入力に関する設定を行う
void UGameOverWidget::SetInputSetting()
{
	// UI入力モードに設定をする
	this->SetKeyboardFocus();
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetInputMode(InputModeData);
}

// キー入力
FReply UGameOverWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == FKey("r"))
	{
		//MoveGameLevel();
		ULevelMover* levelMover = NewObject<ULevelMover>();

		if (levelMover)
		{
			// 死亡したステージに移動
			// TODO死亡したステージを保持する変数から参照するようにする
			levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_STAGE_ONE));
			return FReply::Handled();
		}
	}

	if (InKeyEvent.GetKey() == FKey("t"))
	{
		ULevelMover* levelMover = NewObject<ULevelMover>();

		if (levelMover)
		{
			// タイトルレベルに遷移
			levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_TITLE));
			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}