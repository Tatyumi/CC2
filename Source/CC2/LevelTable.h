// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelTable.generated.h"

/**
 *
 */

UENUM()
enum class ELevels : uint8
{
	LEVEL_TITLE			UMETA(DisplayName = "Title"),
	LEVEL_STAGE_ONE		UMETA(DisplayName = "Stage01"),
	LEVEL_GAMEOVER		UMETA(DisplayName = "GameOver")
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