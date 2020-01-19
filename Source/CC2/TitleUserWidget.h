// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleUserWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class CC2_API UTitleUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "UI")
		UTextBlock* TitleTxt;

	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
		UButton* StartBtn;

protected:
	// Called when the game starts or when spawned
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
		void MoveGameLevel();
};
