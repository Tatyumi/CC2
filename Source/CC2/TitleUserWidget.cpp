// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleUserWidget.h"
#include "LevelMover.h"
#include "LevelTable.h"

#include "Components/Button.h"


void UTitleUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


// キー入力
FReply UTitleUserWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == FKey("w"))
	{
		//MoveGameLevel();
		ULevelMover* levelMover = NewObject<ULevelMover>();

		if (levelMover)
		{
			// ステージ1に移動
			levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_STAGE_ONE));
			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}


// インプットに関する設定を行う
void UTitleUserWidget::SetInputSetting()
{
	// UI入力モードに設定をする
	this->SetKeyboardFocus();
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetInputMode(InputModeData);
}