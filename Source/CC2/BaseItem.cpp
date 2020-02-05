// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "PlayModeWidget.h"
#include "CC2GameModeBase.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// ��]���x
static const float ROTATIOM_SPEED = 1.0f;
// �A�C�e���X�R�A
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

	// ��]
	AddActorWorldRotation(FRotator(0.0f, ROTATIOM_SPEED, 0.0f));
}

// �A�C�e���擾����
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

	// �X�R�A���Z����
	PlayModeWidget->DisplayAddScore(Score);
	Destroy(this);
}


void ABaseItem::InitializeComponent()
{
	// �{�b�N�X�R���|�[�l���g����
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	if (BoxComponent)
	{
		BoxComponent->SetSimulatePhysics(false);
		BoxComponent->SetCollisionProfileName(TEXT("Item"));
		BoxComponent->SetGenerateOverlapEvents(true);
	}

	// �X�^�e�B�b�N�R���|�[�l���g����
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