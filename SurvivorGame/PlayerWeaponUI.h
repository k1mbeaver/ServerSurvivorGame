// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWeaponUI.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UPlayerWeaponUI : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ProjectileText;

	UPROPERTY(Meta = (BindWidget))
		class UImage* WeaponUI;

	UPROPERTY(Meta = (BindWidget))
		class UImage* ProjectileUI;

protected:
	virtual void NativeOnInitialized() override;

public:
	// 사용할 함수들을 정리
};
