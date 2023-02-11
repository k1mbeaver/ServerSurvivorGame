// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeaponUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MyGameInstance.h"

void UPlayerWeaponUI::NativeOnInitialized()
{
	ProjectileText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ProjectileText")));
	WeaponUI = Cast<UImage>(GetWidgetFromName(TEXT("WeaponUI")));
	ProjectileUI = Cast<UImage>(GetWidgetFromName(TEXT("ProjectileUI")));
}