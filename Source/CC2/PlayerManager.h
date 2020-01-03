// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerManager.generated.h"

UCLASS()
class CC2_API APlayerManager : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* MainCameraSpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* MainCameraComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 前後移動
	UFUNCTION()
		void MoveForward(float Value);

	// 左右移動
	UFUNCTION()
		void MoveRight(float Value);

	// ジャンプ開始処理
	UFUNCTION()
		void StartJump();

	// ジャンプ終了処理
	UFUNCTION()
		void EndJump();

	// 視点回転処理
	UFUNCTION()
		void RotateView(float Value);
};