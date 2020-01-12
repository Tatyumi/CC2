// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelTable.generated.h"

/**
 *
 */

UENUM()
enum ELevels
{
	LEVEL_TITLE			UMETA(DisplayName = "Title"),
	LEVEL_STAGE_ONE		UMETA(DisplayName = "Stage01"),
	LEVEL_TEST_MAP		UMETA(DisplayName = "TestMap")
};

USTRUCT()
struct FLevelData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FLevelData()
	{
		ID = 0;
	}

	UPROPERTY(EditAnywhere, category = "Level")
		uint16 ID;

	UPROPERTY(EditAnywhere, category = "Level")
		FName LevelName;
};