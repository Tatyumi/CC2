// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMover.h"
#include "Engine/DataTable.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

ULevelMover::ULevelMover()
{
	// �p�X����LevelData�̎擾
	static ConstructorHelpers::FObjectFinder<UDataTable>
		LevelDataObject(TEXT("/Game/Blueprints/BP_LevelData"));

	if (LevelDataObject.Succeeded())
	{
		LevelTable = LevelDataObject.Object;
	}
}

// �w�肵�����x���ɑJ��
void ULevelMover::MoveLevel(const UObject* World, int Id)
{
	if (!LevelTable)
	{
		return;
	}

	// �e�[�u���̗񖼂��擾
	auto Names = LevelTable->GetRowNames();

	for (int i = 0; i < Names.Num(); i++)
	{
		// �w��̍s���擾
		FLevelData* record = LevelTable->FindRow<FLevelData>(Names[i], FString());

		// �w���ID������
		if (record->ID == Id)
		{
			// �w���ID�̏ꍇ

			// ���x����J�ڂ���
			if (World)
			{
				UGameplayStatics::OpenLevel(World, record->LevelName);
				return;
			}
		}
	}
}