// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleUserWidget.h"
#include "LevelMover.h"
#include "LevelTable.h"

#include "Components/Button.h"


void UTitleUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


// �L�[����
FReply UTitleUserWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == FKey("w"))
	{
		//MoveGameLevel();
		ULevelMover* levelMover = NewObject<ULevelMover>();

		if (levelMover)
		{
			// �X�e�[�W1�Ɉړ�
			levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_STAGE_ONE));
			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}


// �C���v�b�g�Ɋւ���ݒ���s��
void UTitleUserWidget::SetInputSetting()
{
	// UI���̓��[�h�ɐݒ������
	this->SetKeyboardFocus();
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetInputMode(InputModeData);
}