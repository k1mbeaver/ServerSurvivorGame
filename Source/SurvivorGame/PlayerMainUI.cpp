// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMainUI.h"
#include "PlayerGageUI.h"
#include "PlayerWeaponUI.h"
#include "PlayerInventoryUI.h"
#include "PlayerGameEndUI.h"

void UPlayerMainUI::SetHealthPersent(float PlayerHP)
{
	PlayerGageUI->SetHealthPersent(PlayerHP);
}

void UPlayerMainUI::SetStaminaPersent(float PlayerStamina)
{
	PlayerGageUI->SetStaminaPersent(PlayerStamina);
}

void UPlayerMainUI::SetImage(UTexture2D* CurrentImage)
{
	PlayerWeaponUI->SetImage(CurrentImage);
}
void UPlayerMainUI::SetImageUse()
{
	PlayerWeaponUI->SetImageUse();
}

void UPlayerMainUI::SetImageNotUse()
{
	PlayerWeaponUI->SetImageNotUse();
}

void UPlayerMainUI::SetImageVisible()
{
	PlayerWeaponUI->SetImageVisible();
}

void UPlayerMainUI::SetImageHidden()
{
	PlayerWeaponUI->SetImageHidden();
}

void UPlayerMainUI::SetProjectileText(int nProjectile)
{
	PlayerWeaponUI->SetProjectileText(nProjectile);
}

void UPlayerMainUI::SetDefaultText(int nProjectile)
{
	PlayerWeaponUI->SetDefaultText(nProjectile);
}

void UPlayerMainUI::SetTextVisible()
{
	PlayerWeaponUI->SetTextVisible();
}

void UPlayerMainUI::SetTextHidden()
{
	PlayerWeaponUI->SetTextHidden();
}

void UPlayerMainUI::SetInventoryVisible()
{
	PlayerInventoryUI->SetVisible();
}

void UPlayerMainUI::SetInventoryHidden()
{
	PlayerInventoryUI->SetHidden();
}

void UPlayerMainUI::SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	PlayerInventoryUI->SetListInit(nIndex, strName, nCount, setImage);
}

void UPlayerMainUI::SetListCount(int nIndex, int nCount)
{
	PlayerInventoryUI->SetListCount(nIndex, nCount);
}

void UPlayerMainUI::SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	PlayerInventoryUI->SetListView(nIndex, strName, nCount, setImage);
}

void UPlayerMainUI::ListUpdate()
{
	PlayerInventoryUI->ListUpdate();
}

void UPlayerMainUI::SetWeaponImage(UTexture2D* setImage)
{
	PlayerInventoryUI->SetWeaponImage(setImage);
}

void UPlayerMainUI::SetEndVisible()
{
	PlayerEndUI->SetVisible();
}

void UPlayerMainUI::SetEndHidden()
{
	PlayerEndUI->SetHidden();
}

void UPlayerMainUI::SetWin()
{
	PlayerEndUI->SetWin();
}

void UPlayerMainUI::SetLose()
{
	PlayerEndUI->SetLose();
}