// Fill out your copyright notice in the Description page of Project Settings.


#include "CC2GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "BasePlayer.h"

// �R���X�g���N�^
ACC2GameModeBase::ACC2GameModeBase()
{
	DefaultPawnClass = ABasePlayer::StaticClass();
}
