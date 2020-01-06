// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"
#include "Kismet/GameplayStatics.h"
#include "TestUMGController.h"

// ��]���x
static const float ROTATIOM_SPEED = 1.0f;

// Sets default values
AItemManager::AItemManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �R���|�[�l���g����
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// �����V���~���[�V��������
	BoxComponent->SetSimulatePhysics(false);
	BoxComponent->SetCollisionProfileName(TEXT("Item"));


	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetSimulatePhysics(false);
		StaticMeshComponent->AttachTo(BoxComponent);
		BoxComponent->SetGenerateOverlapEvents(true);
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemManager::TriggerEnter);
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

	// ��]
	AddActorWorldRotation(FRotator(0.0f, ROTATIOM_SPEED, 0.0f));
}

void AItemManager::TriggerEnter( UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// �X�R�A���Z����
	ATestUMGController* testUMGController = Cast<ATestUMGController>(UGameplayStatics::GetPlayerController(this, 0));
	playModeWidget = Cast<UPlayModeWidget>(testUMGController->PlayModeWidget);
	if (playModeWidget)
	{
		playModeWidget->DisplayAddScore(Point);
	}

	Destroy(this);
}