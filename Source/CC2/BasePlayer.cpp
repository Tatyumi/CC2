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


// スプリングアームのX軸角度
static const float SPRINGARM_PITCH = -10.0f;

// カメラ回転速度
static const float CAMERA_ROTATE_SPEED = -1.5f;

// Sets default values
ABasePlayer::ABasePlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// スプリングアームコンポーネント生成
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

	// メインカメラコンポーネント生成
	MainCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));

	if (MainCameraComponent)
	{
		if (MainCameraSpringArm)
		{
			// スプリングアームにアタッチ
			MainCameraComponent->SetupAttachment(MainCameraSpringArm, USpringArmComponent::SocketName);
		}
	}

	// カプセルコンポーネントを取得
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

	// 移動処理
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);

	// ジャンプ処理
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABasePlayer::EndJump);

	// 視点回転処理
	PlayerInputComponent->BindAxis("RotateView", this, &ABasePlayer::RotateView);

	// 視点初期化処理
	PlayerInputComponent->BindAction("InitializeView", IE_Pressed, this, &ABasePlayer::ResetView);

	// ポーズ処理
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ABasePlayer::Pause);
}

// 前後移動
void ABasePlayer::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

// 左右移動
void ABasePlayer::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

// ジャンプ開始処理
void ABasePlayer::StartJump()
{
	bPressedJump = true;
}

// ジャンプ終了処理
void ABasePlayer::EndJump()
{
	bPressedJump = false;
}

// 視点回転処理
void ABasePlayer::RotateView(float Value)
{
	MainCameraSpringArm->AddRelativeRotation(FRotator(0.0f, Value * CAMERA_ROTATE_SPEED, 0.0f));
}

// 視点初期化処理
void ABasePlayer::ResetView()
{
	// プレイヤーの真後ろに配置するように角度を設定
	MainCameraSpringArm->SetRelativeRotation(FRotator(SPRINGARM_PITCH, GetActorRotation().Yaw, 0.0f));
}

void ABasePlayer::TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// 接触したActorのチェック
	if ((OtherActor == nullptr) && (OtherActor == this) && (OtherComp == nullptr))
	{
		return;
	}

	// OtherActor判別

	ABaseItem* item = Cast<ABaseItem>(OtherActor);

	// Itemの場合
	if (item)
	{
		item->Pickedup();
		return;
	}

	IEventOccurable* pointInterface = Cast<IEventOccurable>(OtherActor);

	// EventPointの場合
	if (pointInterface)
	{
		pointInterface->Event();
		return;
	}


	ABaseEnemy* enemy = Cast<ABaseEnemy>(OtherActor);

	// Enemyの場合
	if (enemy)
	{
		// ゲームオーバーレベルに遷移
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