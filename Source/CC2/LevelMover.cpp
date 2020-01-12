// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMover.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

ULevelMover::ULevelMover()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		LevelDataObject(TEXT("/Game/Blueprints/BP_DataTable"));

	if (LevelDataObject.Succeeded())
	{
		LevelTable = LevelDataObject.Object;
	}
}

// 指定したレベルに遷移
void ULevelMover::MoveLevel(const UObject* WorldContextObject, int Id)
{
	if (!LevelTable)
	{
		return;
	}

	// テーブルの列名を取得
	auto Names = LevelTable->GetRowNames();

	for (int i = 0; i < Names.Num(); i++)
	{
		// 指定の行を取得
		FLevelData* record = LevelTable->FindRow<FLevelData>(Names[i], FString());

		// 指定のIDか判別
		if (record->ID == Id)
		{
			// 指定のIDの場合

			// レベルを遷移する
			UWorld* world = GEngine->GetWorldFromContextObject(WorldContextObject);
			if (world)
			{
				UGameplayStatics::OpenLevel(world, record->LevelName);
				return;
			}
		}
	}
}