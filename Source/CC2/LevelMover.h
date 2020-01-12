// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelTable.h"
#include "LevelMover.generated.h"

class UDataTable;

UCLASS()
class CC2_API ULevelMover : public UObject
{
	GENERATED_BODY()

public:
	ULevelMover();

	// Žw’è‚µ‚½ƒŒƒxƒ‹‚É‘JˆÚ
	UFUNCTION(meta = (WorldContext = WorldContextObject))
		void MoveLevel(const UObject* WorldContextObject, int Id);

private:

	UPROPERTY(EditAnywhere)
		UDataTable* LevelTable;

	UPROPERTY(EditAnywhere)
		TArray<FLevelData>Table;

};
