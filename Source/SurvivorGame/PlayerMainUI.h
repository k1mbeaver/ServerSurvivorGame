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

	UPROPERTY(Meta = (BindWidget))
		class UPlayerInventoryUI* PlayerInventoryUI;

	UPROPERTY(Meta = (BindWidget))
		class UPlayerGameEndUI* PlayerEndUI;

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
	void SetTextVisible();
	void SetTextHidden();

	// InventoryUI
	void SetInventoryVisible();
	void SetInventoryHidden();
	void SetListCount(int nIndex, int nCount);
	void SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage);
	void SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage);
	void ListUpdate();
	void SetWeaponImage(UTexture2D* setImage);

	// EndUI
	void SetEndVisible();
	void SetEndHidden();
	void SetWin();
	void SetLose();
};
