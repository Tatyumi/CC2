// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerManager.h"
#include "CC2GameModeBase.h"

// Sets default values
APlayerManager::APlayerManager()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// �X�v�����O�A�[���R���|�[�l���g����
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

	// �R���|�[�l���g����
	MainCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	// �|�[������]����
	//MainCameraComponent->bUsePawnControlRotation = true;
	// �X�v�����O�A�[���ɃA�^�b�`
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

	// �ړ�����
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerManager::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerManager::MoveRight);

	// �W�����v����
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerManager::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerManager::EndJump);

	// ���_��]����
	PlayerInputComponent->BindAxis("RotateView", this, &APlayerManager::RotateView);

	// ���_����������
	PlayerInputComponent->BindAction("InitializeView", IE_Pressed, this, &APlayerManager::InitializeView);
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
	MainCameraSpringArm->AddRelativeRotation(FRotator(0, Value, 0));
}

// ���_�ʒu����������
void APlayerManager::InitializeView()
{
	MainCameraSpringArm->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));
}