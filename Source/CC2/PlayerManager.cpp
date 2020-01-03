// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerManager.h"
#include "CC2GameModeBase.h"

// Sets default values
APlayerManager::APlayerManager()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// スプリングアームコンポーネント生成
	MainCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainCameraSpringArm"));

	MainCameraSpringArm->SetupAttachment(RootComponent);
	MainCameraSpringArm->TargetArmLength = 400.0f;
	MainCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-10.0f, 0.0f, 0.0f));
	MainCameraSpringArm->bEnableCameraLag = true;
	MainCameraSpringArm->CameraLagSpeed = 3.0f;
	MainCameraSpringArm->bUsePawnControlRotation = false;
	MainCameraSpringArm->bInheritYaw = false;
	MainCameraSpringArm->bInheritPitch = true;
	MainCameraSpringArm->bInheritRoll = true;

	// コンポーネント生成
	MainCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	// ポーンが回転制御
	//MainCameraComponent->bUsePawnControlRotation = true;
	// スプリングアームにアタッチ
	MainCameraComponent->SetupAttachment(MainCameraSpringArm, USpringArmComponent::SocketName);
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
	PlayerInputComponent->BindAction("InitializeView", IE_Pressed, this, &APlayerManager::InitializeView);
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
	MainCameraSpringArm->AddRelativeRotation(FRotator(0, Value, 0));
}

// 視点位置初期化処理
void APlayerManager::InitializeView()
{
	MainCameraSpringArm->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));
}