// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeaponUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MyGameInstance.h"

void UPlayerWeaponUI::NativeOnInitialized()
{
	ProjectileText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ProjectileText")));
	TextSlash = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextSlash")));
	DefaultText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DefaultText")));
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

void UPlayerWeaponUI::SetProjectileText(int nProjectile)
{
	FString myStr = FString::FromInt(nProjectile);
	FText myText = FText::FromString(myStr);

	ProjectileText->SetText(myText);
}

void UPlayerWeaponUI::SetDefaultText(int nProjectile)
{
	FString myStr = FString::FromInt(nProjectile);
	FText myText = FText::FromString(myStr);

	DefaultText->SetText(myText);
}

void UPlayerWeaponUI::SetTextHidden()
{
	ProjectileText->SetVisibility(ESlateVisibility::Hidden);
	DefaultText->SetVisibility(ESlateVisibility::Hidden);
	TextSlash->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerWeaponUI::SetTextVisible()
{
	ProjectileText->SetVisibility(ESlateVisibility::Visible);
	DefaultText->SetVisibility(ESlateVisibility::Visible);
	TextSlash->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerWeaponUI::SetHidden()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerWeaponUI::SetVisible()
{
	SetVisibility(ESlateVisibility::Visible);
}