// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class UCapsuleComponent;
class AActor;

UCLASS()
class CC2_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
		void MoveSpecifiedPos(FVector SpecifiedPos, float moveSpeed, float DeltaTime);

private:
	UPROPERTY()
		UCapsuleComponent* EnemyCollision;

	UPROPERTY()
		bool IsWait = true;

	UPROPERTY()
		FVector HomePos;

	UPROPERTY()
		FRotator InitializeRotate;

protected:
	UPROPERTY(EditAnywhere)
		float MoveSpeed = 2.0f;

	UPROPERTY(EditAnywhere)
		float BackSpeed = 1.0f;
};