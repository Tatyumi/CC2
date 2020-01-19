// Fill out your copyright notice in the Description page of Project Settings.


#include "CC2GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "PlayerManager.h"

// コンストラクタ
ACC2GameModeBase::ACC2GameModeBase()
{
	DefaultPawnClass = APlayerManager::StaticClass();
}
