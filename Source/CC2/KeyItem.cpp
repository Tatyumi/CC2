// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyItem.h"
#include "PlayModeWidget.h"
#include "CC2GameModeBase.h"
#include "BaseLevelScriptActor.h"
#include "EventOccurable.h"

#include "Kismet/GameplayStatics.h"

// �A�C�e���X�R�A
static const int KEY_ITEM_SCORE = 1000;

AKeyItem::AKeyItem() : ABaseItem(KEY_ITEM_SCORE)
{
}


// �A�C�e���擾����
void AKeyItem::Pickedup()
{
	ACC2GameModeBase* gameMode = Cast<ACC2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (gameMode == nullptr)
	{
		return;
	}

	// �C�x���g�|�C���g�̐؂�ւ�
	gameMode->SwitchEventPoints();

	UPlayModeWidget* PlayModeWidget = Cast<UPlayModeWidget>(gameMode->GetCurrentWidget());

	if (PlayModeWidget == nullptr)
	{
		return;
	}

	// �X�R�A���Z����
	PlayModeWidget->DisplayAddScore(Score);
	Destroy(this);
}