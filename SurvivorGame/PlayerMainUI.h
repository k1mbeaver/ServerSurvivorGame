// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMainUI.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UPlayerMainUI : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(Meta = (BindWidget))
		class UPlayerGageUI* PlayerGageUI;

	UPROPERTY(Meta = (BindWidget))
		class UPlayerWeaponUI* PlayerWeaponUI;

public:
	// GageUI
	void SetHealthPersent(float PlayerHP);
	void SetStaminaPersent(float PlayerStamina);

	// WeaponUI
	void SetImage(UTexture2D* CurrentImage);
	void SetImageUse();
	void SetImageNotUse();
	void SetImageVisible();
	void SetImageHidden();
	void SetProjectileText(int nProjectile);
	void SetDefaultText(int nProjectile);
};
