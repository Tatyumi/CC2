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

// �^�C�g����ʂɑJ��
void UGameOverWidget::MoveTitle()
{
	ULevelMover* levelMover = NewObject<ULevelMover>();
	levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_TITLE));
}

// �ĊJ
void UGameOverWidget::ReStart()
{

	ULevelMover* levelMover = NewObject<ULevelMover>();
	// TODO���S�����X�e�[�W��ێ�����ϐ�����Q�Ƃ���悤�ɂ���
	levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_STAGE_ONE));
}