// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BaseLevelScriptActor.generated.h"

class UUserWidget;
class AStartPoint;
class AGoalPoint;

UCLASS()
class CC2_API ABaseLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UUserWidget* GetWidget() const { return Widget; }

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget>SubWidget;

	UPROPERTY(EditAnywhere, Category = "Point")
		TSubclassOf<class AStartPoint> SubStartPoint;

	UPROPERTY(EditAnywhere, Category = "Point")
		TSubclassOf<class AGoalPoint> SubGoalPoint;

	// �E�B�W�b�g
	UPROPERTY()
		UUserWidget* Widget;

	// �X�^�[�g�n�_
	UPROPERTY()
		AStartPoint* StartPoint;

	// �S�[���n�_
	UPROPERTY()
		AGoalPoint* GoalPoint;
};