// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerItemData.h"

void UInventoryItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
}

void UInventoryItemWidget::OnItemClicked()
{
	return;
}

void UInventoryItemWidget::SetData(class UPlayerItemData* Data)
{
	SetItemCount(Data->GetItemCount());
	SetItemName(Data->GetItemName());
	SetItemImage(Data->GetItemImage());
}

void UInventoryItemWidget::SetItemCount(int nCount)
{
	FString strCount = FString::FromInt(nCount);
	ItemCount->SetText(FText::FromString(strCount));
}

void UInventoryItemWidget::SetItemName(FString setName)
{
	ItemName->SetText(FText::FromString(setName));
}

void UInventoryItemWidget::SetItemImage(UTexture2D* setImage)
{
	ItemImage->SetBrushFromTexture(setImage);
}

UPlayerItemData* UInventoryItemWidget::CastToPlayerItemData(UObject* ListItemData)
{
	UPlayerItemData* PlayerItemData = Cast<UPlayerItemData>(ListItemData);
	return PlayerItemData;
}