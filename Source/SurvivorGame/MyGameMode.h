// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

		AMyGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override; // 이과정에서 플레이어 설정이 진행된다.
};
