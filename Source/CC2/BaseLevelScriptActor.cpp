// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelScriptActor.h"
#include "StartPoint.h"
#include "GoalPoint.h"
#include "CC2GameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// �C�x���g�|�C���g�̍��W
static const FVector EVENT_POINT_POS = FVector(-810.0f, 10.0f, 110.0f);

void ABaseLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	ACC2GameModeBase* gameMode = Cast<ACC2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (SubWidget != nullptr)
	{
		// �E�B�W�b�g�𐶐�
		Widget = CreateWidget<UUserWidget>(GetWorld(), SubWidget);

		if (Widget != nullptr)
		{
			// �E�B�W�b�g��\��
			Widget->AddToViewport();

			if (gameMode)
			{
				// ���ݕ\�����Ă���E�B�W�b�g���擾
				gameMode->SetCurrentWidget(Widget);
			}
		}
	}

	if (SubStartPoint)
	{
		// �X�^�[�g�|�C���g�𐶐�
		StartPoint = GetWorld()->SpawnActor<AStartPoint>(SubStartPoint, EVENT_POINT_POS, FRotator::ZeroRotator);

		if (StartPoint)
		{
			StartPoint->SetActorEnableCollision(true);

			if (gameMode)
			{
				// �X�^�[�g�n�_�̎擾
				gameMode->SetEventPoint(StartPoint);
			}
		}
	}

	if (SubGoalPoint)
	{
		// �S�[���|�C���g�𐶐�
		GoalPoint = GetWorld()->SpawnActor<AGoalPoint>(SubGoalPoint, EVENT_POINT_POS, FRotator::ZeroRotator);
		if (GoalPoint)
		{
			// �S�[���n�_�̎擾
			gameMode->SetEventPoint(GoalPoint);
		}
	}
}