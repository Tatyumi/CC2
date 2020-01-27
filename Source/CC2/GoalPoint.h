// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventOccurable.h"
#include "GoalPoint.generated.h"

class UBoxComponent;

UCLASS()
class CC2_API AGoalPoint : public AActor, public IEventOccurable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGoalPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Event() override;

private:

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxComponent;
};
