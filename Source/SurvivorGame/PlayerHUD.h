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
	// 함수 정리

	void SetHealthPersent(float PlayerHP);
	void SetStaminaPersent(float PlayerStamina);
	void SetImage(UTexture2D* CurrentImage);
	void SetImageUse();
	void SetImageNotUse();
	void SetImageVisible();
	void SetImageHidden();
	void SetProjectileText(int nProjectile);
	void SetDefaultText(int nProjectile);
	void SetTextVisible();
	void SetTextHidden();

	// 인벤토리
	void SetInventoryVisible();
	void SetInventoryHidden();
	void SetListCount(int nIndex, int nCount);
	void SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage);
	void SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage);
	void ListUpdate();
	void SetWeaponImage(UTexture2D* setImage);

private:
	TSubclassOf<class UPlayerMainUI> MainUIClass;
	class UPlayerMainUI* MainUIObject;

private:
	bool CheckUIObject();
	bool CreateUIObject();
};
