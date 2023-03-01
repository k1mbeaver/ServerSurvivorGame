// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGageUI.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "MyGameInstance.h"

void UPlayerGageUI::NativeOnInitialized()
{
	HealthPersent = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthPersent")));
	StaminaPersent = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaPersent")));
}

void UPlayerGageUI::SetHealthPersent(float PlayerHP)
{
	HealthPersent->SetPercent(PlayerHP);
}

void UPlayerGageUI::SetStaminaPersent(float PlayerStamina)
{
	StaminaPersent->SetPercent(PlayerStamina);
}