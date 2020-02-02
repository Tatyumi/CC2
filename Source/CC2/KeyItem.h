// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "KeyItem.generated.h"

class AStartPoint;
class AGoalPoint;
class UEventOccurable;

UCLASS()
class CC2_API AKeyItem : public ABaseItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKeyItem();

	// ƒAƒCƒeƒ€æ“¾ˆ—
		virtual void Pickedup() override;
};