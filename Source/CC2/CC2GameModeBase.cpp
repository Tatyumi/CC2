// Fill out your copyright notice in the Description page of Project Settings.


#include "CC2GameModeBase.h"
#include "BasePlayer.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ACC2GameModeBase::ACC2GameModeBase()
	:IsPause(false)
{
	DefaultPawnClass = ABasePlayer::StaticClass();

}

void ACC2GameModeBase::BeginPlay()
{
	if (SubPauseWidget != nullptr)
	{
		// ポーズウィジットを取得
		PauseWidget = CreateWidget<UUserWidget>(GetWorld(), SubPauseWidget);
	}
}


// イベントポイントのコリジョン切り替え
void ACC2GameModeBase::SwitchEventPoints()
{
	for (auto eventPoint : EventPoints)
	{
		AActor* actor = Cast<AActor>(eventPoint);
		actor->SetActorEnableCollision(!actor->GetActorEnableCollision());
	}
}


// ポーズモード切替
void ACC2GameModeBase::SwitchPauseMode()
{
	if (CurrentWidget == nullptr)
	{
		return;
	}

	if (PauseWidget == nullptr)
	{
		return;
	}

	// 現状がポーズ状態か判別
	if (IsPause)
	{
		// ポーズ状態の場合

		// ポーズウィジットを非表示
		PauseWidget->RemoveFromParent();

		// 表示していたウィジットを表示
		CurrentWidget->AddToViewport();

		// ゲーム入力モードに設定をする
		FInputModeGameOnly InputModeData;
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->SetInputMode(InputModeData);
	}
	else
	{
		// ポーズ状態でない場合

		// 現在表示しているウィジットを非表示
		CurrentWidget->RemoveFromParent();

		// ポーズウィジットを表示
		PauseWidget->AddToViewport();

		// キー入力を受け付けるようにするためフォーカスを有効にずる
		PauseWidget->bIsFocusable = true;

		// UI入力モードに設定をする
		PauseWidget->SetKeyboardFocus();
		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(PauseWidget->TakeWidget());
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->SetInputMode(InputModeData);
	}

	// ポーズ状態を切り替える
	UGameplayStatics::SetGamePaused(GetWorld(), !IsPause);
	IsPause = !IsPause;
}
