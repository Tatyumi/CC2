// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemManager.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class CC2_API AItemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComponent;

	// アイテム取得処理
	UFUNCTION()
		void Pickedup();

private:

	UPROPERTY()
		uint32 Point;
};