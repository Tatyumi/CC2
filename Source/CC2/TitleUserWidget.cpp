// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleUserWidget.h"
#include "Components/Button.h"
#include "LevelMover.h"
#include "LevelTable.h"


void UTitleUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartBtn)
	{
		StartBtn->OnClicked.AddDynamic(this, &UTitleUserWidget::MoveGameLevel);
	}
}


void UTitleUserWidget::MoveGameLevel()
{
	ULevelMover* levelMover = NewObject<ULevelMover>();
	//levelMover->MoveLevel(GetWorld(), 1);
	levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_STAGE_ONE));
}