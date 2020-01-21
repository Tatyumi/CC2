// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

#include "Kismet/GameplayStatics.h"


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

	// ���g�̈ʒu����O�����Ƀ��C���g���[�X��\��
	FVector StartPos = EnemyCollision->GetComponentLocation();
	FVector ForwardVec = EnemyCollision->GetForwardVector();
	FVector EndPos = (StartPos + (ForwardVec * DISTANCE));

	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red, false, 1, 0, 1);

	// TODO ���C���g���[�X�Ƀv���C���[���ڐG�������̏���
	// �t���O�̐؂�ւ�
	// �t���O����
	// ���v���C���[�̕����ɐi�ށi��莞�ԁH�v���C���[�Ƃ̋����������܂ŁH�j

	// �t���O����
	// ���ҋ@or�ړ�
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

