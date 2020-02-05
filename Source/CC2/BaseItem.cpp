// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "PlayModeWidget.h"
#include "CC2GameModeBase.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// 回転速度
static const float ROTATIOM_SPEED = 1.0f;
// アイテムスコア
static const int BASE_ITEM_SCORE = 100;

// Sets default values// Sets default values
ABaseItem::ABaseItem():Score(BASE_ITEM_SCORE)
{
	PrimaryActorTick.bCanEverTick = true;

	InitializeComponent();
}

ABaseItem::ABaseItem(const int Score):Score(Score)
{
	PrimaryActorTick.bCanEverTick = true;

	InitializeComponent();
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 回転
	AddActorWorldRotation(FRotator(0.0f, ROTATIOM_SPEED, 0.0f));
}

// アイテム取得処理
void ABaseItem::Pickedup()
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

	// スコア加算処理
	PlayModeWidget->DisplayAddScore(Score);
	Destroy(this);
}


void ABaseItem::InitializeComponent()
{
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
}