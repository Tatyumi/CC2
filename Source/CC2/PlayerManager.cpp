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


// スプリングアームのX軸角度
static const float SPRINGARM_PITCH = -10.0f;

// Sets default values
APlayerManager::APlayerManager()
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

	// 移動処理
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerManager::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerManager::MoveRight);

	// ジャンプ処理
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerManager::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerManager::EndJump);

	// 視点回転処理
	PlayerInputComponent->BindAxis("RotateView", this, &APlayerManager::RotateView);

	// 視点初期化処理
	PlayerInputComponent->BindAction("InitializeView", IE_Pressed, this, &APlayerManager::ResetView);
}

// 前後移動
void APlayerManager::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

// 左右移動
void APlayerManager::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

// ジャンプ開始処理
void APlayerManager::StartJump()
{
	bPressedJump = true;
}

// ジャンプ終了処理
void APlayerManager::EndJump()
{
	bPressedJump = false;
}

// 視点回転処理
void APlayerManager::RotateView(float Value)
{
	MainCameraSpringArm->AddRelativeRotation(FRotator(0.0f, Value, 0.0f));
}

// 視点初期化処理
void APlayerManager::ResetView()
{
	// プレイヤーの真後ろに配置するように角度を設定
	MainCameraSpringArm->SetRelativeRotation(FRotator(SPRINGARM_PITCH, GetActorRotation().Yaw, 0.0f));
}

void APlayerManager::TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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
		// ゲームオーバー画面に遷移
		ULevelMover* levelMover = NewObject<ULevelMover>();
		levelMover->MoveLevel(GetWorld(), static_cast<int>(ELevels::LEVEL_GAMEOVER));

		return;
	}
}