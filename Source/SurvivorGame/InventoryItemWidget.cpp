// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerItemData.h"
#include "MyGameInstance.h"

void UInventoryItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	bgImage = Cast<UImage>(GetWidgetFromName(TEXT("bgImage")));
}

void UInventoryItemWidget::PlayerClick()
{
	bgImage->SetBrushTintColor(SelectColor);
	IsSelected = true;
	return;
}

void UInventoryItemWidget::PlayerHover()
{
	//bgImage-> // 여기해서 호버되었을 때 이미지 값 조정
	if (IsSelected == false)
	{
		bgImage->SetBrushTintColor(HoverColor);
	}
	return;
}

void UInventoryItemWidget::PlayerHoverEnd()
{
	// 여기해서 호버가 끝났을 때 이미지값을 조정
	if (IsSelected == false)
	{
		bgImage->SetBrushTintColor(HoverEndColor);
	}

	else
	{
		bgImage->SetBrushTintColor(HoverEndColor);
		IsSelected = false;
	}
	return;
}

void UInventoryItemWidget::SetData(class UPlayerItemData* Data)
{
	SetItemCount(Data->GetItemCount());
	SetItemName(Data->GetItemName());
	SetItemImage(Data->GetItemImage());

	myData = Data;
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

FString UInventoryItemWidget::GetItemID()
{
	return myData->GetItemID();
}