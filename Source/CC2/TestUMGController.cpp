// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUMGController.h"
#include "Blueprint/UserWidget.h"


void ATestUMGController::BeginPlay()
{
	Super::BeginPlay();

	if (wPlayModeWidget)
	{
		PlayModeWidget = CreateWidget<UUserWidget>(this, wPlayModeWidget);

		if (PlayModeWidget)
		{
			// UIを画面に表示
			PlayModeWidget->AddToViewport();
		}
	}
}