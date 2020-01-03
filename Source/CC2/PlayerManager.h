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

	// �O��ړ�
	UFUNCTION()
		void MoveForward(float Value);

	// ���E�ړ�
	UFUNCTION()
		void MoveRight(float Value);

	// �W�����v�J�n����
	UFUNCTION()
		void StartJump();

	// �W�����v�I������
	UFUNCTION()
		void EndJump();

	// ���_��]����
	UFUNCTION()
		void RotateView(float Value);
};