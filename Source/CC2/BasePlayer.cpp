// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayer.h"
#include "CC2GameModeBase.h"
#include "BaseItem.h"
#include "PlayModeWidget.h"
#include "LevelMover.h"
#include "LevelTable.h"
#include "BaseEnemy.h"
#include "EventOccurable.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


// �X�v�����O�A�[����X���p�x
static const float SPRINGARM_PITCH = -10.0f;

// �J������]���x
static const float CAMERA_ROTATE_SPEED = -1.5f;

// Sets default values
ABasePlayer::ABasePlayer()
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
	PlayerCollision = ABasePlayer::GetCapsuleComponent();
	if (PlayerCollision)
	{
		PlayerCollision->OnComponentBeginOverlap.AddDynamic(this, &ABasePlayer::TriggerEnter);
	}
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �ړ�����
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);

	// �W�����v����
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABasePlayer::EndJump);

	// ���_��]����
	PlayerInputComponent->BindAxis("RotateView", this, &ABasePlayer::RotateView);

	// ���_����������
	PlayerInputComponent->BindAction("InitializeView", IE_Pressed, this, &ABasePlayer::ResetView);

	// �|�[�Y����
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ABasePlayer::Pause);
}

// �O��ړ�
void ABasePlayer::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

// ���E�ړ�
void ABasePlayer::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

// �W�����v�J�n����
void ABasePlayer::StartJump()
{
	bPressedJump = true;
}

// �W�����v�I������
void ABasePlayer::EndJump()
{
	bPressedJump = false;
}

// ���_��]����
void ABasePlayer::RotateView(float Value)
{
	MainCameraSpringArm->AddRelativeRotation(FRotator(0.0f, Value * CAMERA_ROTATE_SPEED, 0.0f));
}

// ���_����������
void ABasePlayer::ResetView()
{
	// �v���C���[�̐^���ɔz�u����悤�Ɋp�x��ݒ�
	MainCameraSpringArm->SetRelativeRotation(FRotator(SPRINGARM_PITCH, GetActorRotation().Yaw, 0.0f));
}

void ABasePlayer::TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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
		// �Q�[���I�[�o�[���x���ɑJ��
		ULevelMover* levelMover = NewObject<ULevelMover>();
		levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_GAMEOVER));

		return;
	}
}

void ABasePlayer::Pause()
{
	ACC2GameModeBase* gameMode = Cast<ACC2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->SwitchPauseMode();
}