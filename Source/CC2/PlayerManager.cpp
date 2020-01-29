// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerManager.h"
#include "CC2GameModeBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

#include "BaseItem.h"
#include "PlayModeWidget.h"
#include "LevelMover.h"
#include "LevelTable.h"
#include "BaseEnemy.h"
#include "EventOccurable.h"


// �X�v�����O�A�[����X���p�x
static const float SPRINGARM_PITCH = -10.0f;

// Sets default values
APlayerManager::APlayerManager()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// �X�v�����O�A�[���R���|�[�l���g����
	MainCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainCameraSpringArm"));

	if (MainCameraSpringArm)
	{
		MainCameraSpringArm->SetupAttachment(RootComponent);
		MainCameraSpringArm->TargetArmLength = 400.0f;
		MainCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(SPRINGARM_PITCH, 0.0f, 0.0f));
		MainCameraSpringArm->CameraLagSpeed = 3.0f;
		MainCameraSpringArm->bEnableCameraLag = true;
		MainCameraSpringArm->bUsePawnControlRotation = true;
		MainCameraSpringArm->bInheritYaw = false;
		MainCameraSpringArm->bInheritPitch = true;
		MainCameraSpringArm->bInheritRoll = true;
	}

	// ���C���J�����R���|�[�l���g����
	MainCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));

	if (MainCameraComponent)
	{
		if (MainCameraSpringArm)
		{
			// �X�v�����O�A�[���ɃA�^�b�`
			MainCameraComponent->SetupAttachment(MainCameraSpringArm, USpringArmComponent::SocketName);
		}
	}

	// �J�v�Z���R���|�[�l���g���擾
	PlayerCollision = APlayerManager::GetCapsuleComponent();
	if (PlayerCollision)
	{
		PlayerCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerManager::TriggerEnter);
	}
}

// Called when the game starts or when spawned
void APlayerManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �ړ�����
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerManager::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerManager::MoveRight);

	// �W�����v����
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerManager::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerManager::EndJump);

	// ���_��]����
	PlayerInputComponent->BindAxis("RotateView", this, &APlayerManager::RotateView);

	// ���_����������
	PlayerInputComponent->BindAction("InitializeView", IE_Pressed, this, &APlayerManager::ResetView);
}

// �O��ړ�
void APlayerManager::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

// ���E�ړ�
void APlayerManager::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

// �W�����v�J�n����
void APlayerManager::StartJump()
{
	bPressedJump = true;
}

// �W�����v�I������
void APlayerManager::EndJump()
{
	bPressedJump = false;
}

// ���_��]����
void APlayerManager::RotateView(float Value)
{
	MainCameraSpringArm->AddRelativeRotation(FRotator(0.0f, Value, 0.0f));
}

// ���_����������
void APlayerManager::ResetView()
{
	// �v���C���[�̐^���ɔz�u����悤�Ɋp�x��ݒ�
	MainCameraSpringArm->SetRelativeRotation(FRotator(SPRINGARM_PITCH, GetActorRotation().Yaw, 0.0f));
}

void APlayerManager::TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// �ڐG����Actor�̃`�F�b�N
	if ((OtherActor == nullptr) && (OtherActor == this) && (OtherComp == nullptr))
	{
		return;
	}

	// OtherActor����

	ABaseItem* item = Cast<ABaseItem>(OtherActor);

	// Item�̏ꍇ
	if (item)
	{
		item->Pickedup();
		return;
	}

	IEventOccurable* pointInterface = Cast<IEventOccurable>(OtherActor);

	// EventPoint�̏ꍇ
	if (pointInterface)
	{
		pointInterface->Event();
		return;
	}


	ABaseEnemy* enemy = Cast<ABaseEnemy>(OtherActor);

	// Enemy�̏ꍇ
	if (enemy)
	{
		// �Q�[���I�[�o�[��ʂɑJ��
		ULevelMover* levelMover = NewObject<ULevelMover>();
		levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_GAMEOVER));

		return;
	}
}