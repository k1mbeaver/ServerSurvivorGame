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

void UPlayerWeaponUI::SetImage(UTexture2D* CurrentImage)
{
	WeaponUI->SetBrushFromTexture(CurrentImage);
}

void UPlayerWeaponUI::SetImageUse()
{
	WeaponUI->SetColorAndOpacity(FLinearColor::White);
}

void UPlayerWeaponUI::SetImageNotUse()
{
	WeaponUI->SetColorAndOpacity(FLinearColor::Gray);
}

void UPlayerWeaponUI::SetImageVisible()
{
	WeaponUI->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerWeaponUI::SetImageHidden()
{
	WeaponUI->SetVisibility(ESlateVisibility::Hidden);
}