// Fill out your copyright notice in the Description page of Project Settings.


#include "StartPoint.h"
#include "PlayModeWidget.h"
#include "CC2GameModeBase.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStartPoint::AStartPoint()
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
void AStartPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStartPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStartPoint::Event()
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
	PlayModeWidget->DispMessagePnl();
}