// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "Kismet/GameplayStatics.h"

#include "CC2GameModeBase.h"

// ÉLÅ[ì¸óÕ
FReply UPauseWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == FKey("p"))
	{
		ACC2GameModeBase* gameMode = Cast<ACC2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		gameMode->SwitchPauseMode();
	
		return FReply::Handled();
	}

	return FReply::Unhandled();
}