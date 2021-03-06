// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalPoint.h"
#include "PlayModeWidget.h"
#include "CC2GameModeBase.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoalPoint::AGoalPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// コンポーネント作成
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	if (BoxComponent)
	{
		BoxComponent->SetSimulatePhysics(false);
		BoxComponent->SetCollisionProfileName(TEXT("EventPoint"));
		BoxComponent->SetGenerateOverlapEvents(true);
	}
}

// Called when the game starts or when spawned
void AGoalPoint::BeginPlay()
{
	Super::BeginPlay();

	// コリジョンを非表示
	this->SetActorEnableCollision(false);
}

// Called every frame
void AGoalPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// イベント処理
void AGoalPoint::Event()
{
	ACC2GameModeBase* gameMode = Cast<ACC2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (gameMode == nullptr)
	{
		return;
	}

	UPlayModeWidget* PlayModeWidget = Cast<UPlayModeWidget>(gameMode->GetCurrentWidget());

	if (PlayModeWidget == nullptr)
	{
		return;
	}

	// メッセージパネルを表示
	PlayModeWidget->DispGameClearPnl();
}