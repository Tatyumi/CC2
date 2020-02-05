// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class CC2_API ABaseItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseItem();

	ABaseItem(int Score);

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
		virtual void Pickedup();

private:

	// コンポーネント初期化処理
	UFUNCTION()
		void InitializeComponent();

protected:

	// スコア
	uint32 Score;

};