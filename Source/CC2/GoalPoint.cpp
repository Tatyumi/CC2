// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalPoint.h"
#include "Components/BoxComponent.h"

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

}

// Called every frame
void AGoalPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGoalPoint::Event()
{
	UE_LOG(LogTemp, Warning, TEXT("EndPoint Hit!"));
}