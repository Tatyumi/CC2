// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputModeSetable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInputModeSetable : public UInterface
{
	GENERATED_BODY()
};

class CC2_API IInputModeSetable
{
	GENERATED_BODY()

public:
	UFUNCTION()
		virtual void SetInputSetting();
};
