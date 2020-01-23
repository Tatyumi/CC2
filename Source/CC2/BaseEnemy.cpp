// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// ���_����
static const float DISTANCE = 200.0f;

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// �J�v�Z���R���|�[�l���g���擾
	EnemyCollision = ABaseEnemy::GetCapsuleComponent();
	if (EnemyCollision)
	{
		EnemyCollision->SetCollisionProfileName(TEXT("Enemy"));
	}

	// �����ʒu���擾
	HomePos = EnemyCollision->GetComponentLocation();
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	// �����ʒu�A�p�x���擾
	HomePos = EnemyCollision->GetComponentLocation();
	InitializeRotate = EnemyCollision->GetComponentRotation();
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���g�̈ʒu����O�����Ƀ��C���g���[�X��\��
	FVector StartPos = EnemyCollision->GetComponentLocation();
	FVector ForwardVec = EnemyCollision->GetForwardVector();
	FVector EndPos = (StartPos + (ForwardVec * DISTANCE));

	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red, false, 1, 0, 1);
	//DrawDebugCone(GetWorld(), StartPos, EndPos,100.0f,20.0f,10.0f,10, FColor::Red, false, 1, 0, 1);

	FHitResult OutHit;
	FCollisionQueryParams CollisionQueryParams;

	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, StartPos, EndPos, ECC_Pawn, CollisionQueryParams);

	// ���C���g���[�X�Փ˔���
	if (isHit)
	{
		// �Փ˂����ꍇ

		// �Փ˂���Actor�𔻕�
		if (OutHit.Actor->ActorHasTag(FName("Player")))
		{
			// �v���C���[���Փ˂����ꍇ

			// �v���C���[��ǂ�������
			MoveSpecifiedPos(OutHit.Actor->GetActorLocation(), MoveSpeed, DeltaTime);
			IsWait = false;
		}

		return;
	}

	// �ҋ@��Ԃ�����
	if (!IsWait)
	{
		// �ҋ@��ԂłȂ��ꍇ

		// �����ʒu�ɖ߂�
		MoveSpecifiedPos(HomePos, BackSpeed, DeltaTime);

		// �����ʒu�ɒH�蒅����������
		if (EnemyCollision->GetComponentLocation().X - HomePos.X <= 1.0f
			&& EnemyCollision->GetComponentLocation().Y - HomePos.Y <= 1.0f)
		{
			// �H�蒅�����ꍇ

			// �����̌����ɐݒ�
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

// �w��̍��W�Ɉړ�����
void ABaseEnemy::MoveSpecifiedPos(FVector SpecifiedPos, float moveSpeed, float DeltaTime)
{
	FVector direction;
	FVector enemyPos = EnemyCollision->GetComponentLocation();
	direction = SpecifiedPos - enemyPos;
	direction.Normalize();

	// �w��̍��W�Ɉړ�
	this->SetActorLocation(enemyPos + (direction *  moveSpeed + DeltaTime));

	// �w��̍��W�Ɍ���
	enemyPos.Z = 0;
	SpecifiedPos.Z = 0;
	this->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(enemyPos, SpecifiedPos));
}