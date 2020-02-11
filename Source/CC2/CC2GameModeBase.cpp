// Fill out your copyright notice in the Description page of Project Settings.


#include "CC2GameModeBase.h"
#include "BasePlayer.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ACC2GameModeBase::ACC2GameModeBase()
	:IsPause(false)
{
	DefaultPawnClass = ABasePlayer::StaticClass();

}

void ACC2GameModeBase::BeginPlay()
{
	if (SubPauseWidget != nullptr)
	{
		// �|�[�Y�E�B�W�b�g���擾
		PauseWidget = CreateWidget<UUserWidget>(GetWorld(), SubPauseWidget);
	}
}


// �C�x���g�|�C���g�̃R���W�����؂�ւ�
void ACC2GameModeBase::SwitchEventPoints()
{
	for (auto eventPoint : EventPoints)
	{
		AActor* actor = Cast<AActor>(eventPoint);
		actor->SetActorEnableCollision(!actor->GetActorEnableCollision());
	}
}


// �|�[�Y���[�h�ؑ�
void ACC2GameModeBase::SwitchPauseMode()
{
	if (CurrentWidget == nullptr)
	{
		return;
	}

	if (PauseWidget == nullptr)
	{
		return;
	}

	// ���󂪃|�[�Y��Ԃ�����
	if (IsPause)
	{
		// �|�[�Y��Ԃ̏ꍇ

		// �|�[�Y�E�B�W�b�g���\��
		PauseWidget->RemoveFromParent();

		// �\�����Ă����E�B�W�b�g��\��
		CurrentWidget->AddToViewport();

		// �Q�[�����̓��[�h�ɐݒ������
		FInputModeGameOnly InputModeData;
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->SetInputMode(InputModeData);
	}
	else
	{
		// �|�[�Y��ԂłȂ��ꍇ

		// ���ݕ\�����Ă���E�B�W�b�g���\��
		CurrentWidget->RemoveFromParent();

		// �|�[�Y�E�B�W�b�g��\��
		PauseWidget->AddToViewport();

		// �L�[���͂��󂯕t����悤�ɂ��邽�߃t�H�[�J�X��L���ɂ���
		PauseWidget->bIsFocusable = true;

		// UI���̓��[�h�ɐݒ������
		PauseWidget->SetKeyboardFocus();
		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(PauseWidget->TakeWidget());
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->SetInputMode(InputModeData);
	}

	// �|�[�Y��Ԃ�؂�ւ���
	UGameplayStatics::SetGamePaused(GetWorld(), !IsPause);
	IsPause = !IsPause;
}
