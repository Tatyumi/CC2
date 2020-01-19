// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlayModeWidget.h"
#include "CC2GameModeBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// 回転速度
static const float ROTATIOM_SPEED = 1.0f;

// Sets default values
AItemManager::AItemManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ボックスコンポーネント生成
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	if (BoxComponent)
	{
		BoxComponent->SetSimulatePhysics(false);
		BoxComponent->SetCollisionProfileName(TEXT("Item"));
		BoxComponent->SetGenerateOverlapEvents(true);
	}

	// スタティックコンポーネント生成
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetSimulatePhysics(false);

		if (BoxComponent)
		{
			StaticMeshComponent->AttachTo(BoxComponent);
		}
	}

	Point = 100;
}

// Called when the game starts or when spawned
void AItemManager::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void AItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 回転
	AddActorWorldRotation(FRotator(0.0f, ROTATIOM_SPEED, 0.0f));
}

// アイテム取得処理
void AItemManager::Pickedup()
{
	ACC2GameModeBase* gameMode = Cast<ACC2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (gameMode == nullptr)
	{
		return;
	}

	// TODO Castが可能かどうか判別式が必要かも

	UPlayModeWidget* PlayModeWidget = Cast<UPlayModeWidget>(gameMode->GetCurrentWidget());

	if (PlayModeWidget == nullptr)
	{
		return;
	}

	// スコア加算処理
	PlayModeWidget->DisplayAddScore(Point);
	Destroy(this);
}