// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

#include "Kismet/GameplayStatics.h"


// 視点距離
static const float DISTANCE = 200.0f;

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// カプセルコンポーネントを取得
	EnemyCollision = ABaseEnemy::GetCapsuleComponent();
	if (EnemyCollision)
	{
		EnemyCollision->SetCollisionProfileName(TEXT("Enemy"));
	}
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 自身の位置から前方向にライントレースを表示
	FVector StartPos = EnemyCollision->GetComponentLocation();
	FVector ForwardVec = EnemyCollision->GetForwardVector();
	FVector EndPos = (StartPos + (ForwardVec * DISTANCE));

	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red, false, 1, 0, 1);

	// TODO ライントレースにプレイヤーが接触した時の処理
	// フラグの切り替え
	// フラグが正
	// →プレイヤーの方向に進む（一定時間？プレイヤーとの距離があくまで？）

	// フラグが負
	// →待機or移動
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

