// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerGageUI.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UPlayerGageUI : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* HealthPersent;

	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* StaminaPersent;

protected:
	virtual void NativeOnInitialized() override;

public:
	// 사용할 함수들을 정리
	void SetHealthPersent(float PlayerHP);
	void SetStaminaPersent(float PlayerStamina);
};
