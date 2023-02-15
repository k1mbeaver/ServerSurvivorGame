// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMainUI.h"
#include "PlayerGageUI.h"
#include "PlayerWeaponUI.h"

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