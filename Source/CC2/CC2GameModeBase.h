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
	// コンストラクタ
	ACC2GameModeBase();

	UFUNCTION()
		void SetCurrentWidget(UUserWidget* CurrentWidget) { this->CurrentWidget = CurrentWidget; }

	UFUNCTION()
		UUserWidget* GetCurrentWidget()const { return CurrentWidget; }

	UFUNCTION()
		void SetEventPoint(AActor* Point) { this->EventPoints.Add(Point); }

	// イベント地点の表示切替
	UFUNCTION()
		void SwitchEventPoints();

	// ポーズモード切替
	UFUNCTION()
		void SwitchPauseMode();

protected:
	virtual void BeginPlay() override;


private:

	// 現在表示しているウィジット
	UPROPERTY()
		UUserWidget* CurrentWidget;

	// イベント地点
	UPROPERTY()
		TArray<AActor*> EventPoints;

	// サブポーズウィジット
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget>SubPauseWidget;

	// ポーズウィジット
	UPROPERTY()
		UUserWidget* PauseWidget;

	bool IsPause;
};
