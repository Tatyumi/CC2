// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

	// 初期位置を取得
	HomePos = EnemyCollision->GetComponentLocation();
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	// 初期位置、角度を取得
	HomePos = EnemyCollision->GetComponentLocation();
	InitializeRotate = EnemyCollision->GetComponentRotation();
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
	//DrawDebugCone(GetWorld(), StartPos, EndPos,100.0f,20.0f,10.0f,10, FColor::Red, false, 1, 0, 1);

	FHitResult OutHit;
	FCollisionQueryParams CollisionQueryParams;

	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, StartPos, EndPos, ECC_Pawn, CollisionQueryParams);

	// ライントレース衝突判定
	if (isHit)
	{
		// 衝突した場合

		// 衝突したActorを判別
		if (OutHit.Actor->ActorHasTag(FName("Player")))
		{
			// プレイヤーが衝突した場合

			// プレイヤーを追いかける
			MoveSpecifiedPos(OutHit.Actor->GetActorLocation(), MoveSpeed, DeltaTime);
			IsWait = false;
		}

		return;
	}

	// 待機状態か判別
	if (!IsWait)
	{
		// 待機状態でない場合

		// 初期位置に戻る
		MoveSpecifiedPos(HomePos, BackSpeed, DeltaTime);

		// 初期位置に辿り着いたか判別
		if (EnemyCollision->GetComponentLocation().X - HomePos.X <= 1.0f
			&& EnemyCollision->GetComponentLocation().Y - HomePos.Y <= 1.0f)
		{
			// 辿り着いた場合

			// 初期の向きに設定
			this->SetActorRotation(InitializeRotate);
			IsWait = true;
		}
	}
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 指定の座標に移動する
void ABaseEnemy::MoveSpecifiedPos(FVector SpecifiedPos, float moveSpeed, float DeltaTime)
{
	FVector direction;
	FVector enemyPos = EnemyCollision->GetComponentLocation();
	direction = SpecifiedPos - enemyPos;
	direction.Normalize();

	// 指定の座標に移動
	this->SetActorLocation(enemyPos + (direction *  moveSpeed + DeltaTime));

	// 指定の座標に向く
	enemyPos.Z = 0;
	SpecifiedPos.Z = 0;
	this->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(enemyPos, SpecifiedPos));
}