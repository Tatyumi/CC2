// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 *
 */
UCLASS()
class CC2_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	// ÉLÅ[ì¸óÕ
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)override;
};
