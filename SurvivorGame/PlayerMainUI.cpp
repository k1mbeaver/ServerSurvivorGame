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