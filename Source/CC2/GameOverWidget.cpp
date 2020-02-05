// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Components/Button.h"
#include "LevelMover.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


// ���͂Ɋւ���ݒ���s��
void UGameOverWidget::SetInputSetting()
{
	// UI���̓��[�h�ɐݒ������
	this->SetKeyboardFocus();
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetInputMode(InputModeData);
}

// �L�[����
FReply UGameOverWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == FKey("r"))
	{
		//MoveGameLevel();
		ULevelMover* levelMover = NewObject<ULevelMover>();

		if (levelMover)
		{
			// ���S�����X�e�[�W�Ɉړ�
			// TODO���S�����X�e�[�W��ێ�����ϐ�����Q�Ƃ���悤�ɂ���
			levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_STAGE_ONE));
			return FReply::Handled();
		}
	}

	if (InKeyEvent.GetKey() == FKey("t"))
	{
		ULevelMover* levelMover = NewObject<ULevelMover>();

		if (levelMover)
		{
			// �^�C�g�����x���ɑJ��
			levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_TITLE));
			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}