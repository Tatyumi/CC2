// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CC2GameModeBase.generated.h"


UCLASS()
class CC2_API ACC2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// �R���X�g���N�^
	ACC2GameModeBase();

	UFUNCTION()
		void SetCurrentWidget(UUserWidget* CurrentWidget) { this->CurrentWidget = CurrentWidget; }

	UFUNCTION()
		UUserWidget* GetCurrentWidget()const { return CurrentWidget; }

	UFUNCTION()
		void SetEventPoint(AActor* Point) { this->EventPoints.Add(Point); }

	// �C�x���g�n�_�̕\���ؑ�
	UFUNCTION()
		void SwitchEventPoints();

	// �|�[�Y���[�h�ؑ�
	UFUNCTION()
		void SwitchPauseMode();

protected:
	virtual void BeginPlay() override;


private:

	// ���ݕ\�����Ă���E�B�W�b�g
	UPROPERTY()
		UUserWidget* CurrentWidget;

	// �C�x���g�n�_
	UPROPERTY()
		TArray<AActor*> EventPoints;

	// �T�u�|�[�Y�E�B�W�b�g
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget>SubPauseWidget;

	// �|�[�Y�E�B�W�b�g
	UPROPERTY()
		UUserWidget* PauseWidget;

	bool IsPause;
};
