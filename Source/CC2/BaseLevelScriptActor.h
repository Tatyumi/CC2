// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BaseLevelScriptActor.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class CC2_API ABaseLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UUserWidget* GetWidget() const { return Widget; }

private:
	UPROPERTY()
		UUserWidget* Widget;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget>SubWidget;
};
