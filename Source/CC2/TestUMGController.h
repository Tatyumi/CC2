// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestUMGController.generated.h"

class UUserWidget;

UCLASS()
class CC2_API ATestUMGController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay()override;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget>wPlayModeWidget;

	UUserWidget* PlayModeWidget;
};
