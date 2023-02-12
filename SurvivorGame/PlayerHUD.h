// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	APlayerHUD();
	virtual void BeginPlay() override;

public:
	// �Լ� ����

	void SetHealthPersent(float PlayerHP);
	void SetStaminaPersent(float PlayerStamina);

private:
	TSubclassOf<class UPlayerMainUI> MainUIClass;
	class UPlayerMainUI* MainUIObject;

private:
	bool CheckUIObject();
	bool CreateUIObject();
};
