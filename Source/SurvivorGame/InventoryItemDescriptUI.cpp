// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemDescriptUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UInventoryItemDescriptUI::NativeOnInitialized()
{
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemDescript = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDescript")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
}

void UInventoryItemDescriptUI::SetItemImage(UTexture2D* myItemImage)
{
	ItemImage->SetBrushFromTexture(myItemImage);
}

void UInventoryItemDescriptUI::SetItemName(FString myItemName)
{
	FText myFText = FText::FromString(myItemName);
	ItemName->SetText(myFText);
}

void UInventoryItemDescriptUI::SetItemDescript(FString myItemName)
{
	FText myFText = FText::FromString(myItemName);
	ItemDescript->SetText(myFText);
}