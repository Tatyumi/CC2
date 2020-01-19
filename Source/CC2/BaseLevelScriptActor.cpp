// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelScriptActor.h"
#include "Blueprint/UserWidget.h"
#include "CC2GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ABaseLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	if (SubWidget != nullptr)
	{
		Widget = CreateWidget<UUserWidget>(GetWorld(), SubWidget);

		if (Widget != nullptr)
		{
			Widget->AddToViewport();

			ACC2GameModeBase* gameMode = Cast<ACC2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

			if (gameMode)
			{
				gameMode->SetCurrentWidget(Widget);
			}
		}
	}
}