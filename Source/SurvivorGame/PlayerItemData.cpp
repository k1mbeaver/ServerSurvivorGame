// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerItemData.h"

void UPlayerItemData::SetItemIndex(int nIndex)
{
	ItemIndex = nIndex;
}

void UPlayerItemData::SetItemDescript(FString strDescript)
{
	ItemDescript = strDescript;
}

void UPlayerItemData::SetItemName(FString strName)
{
	ItemName = strName;
}

void UPlayerItemData::SetItemType(FString strItemType)
{
	ItemType = strItemType;
}

void UPlayerItemData::SetItemID(FString strItemID)
{
	ItemID = strItemID;
}

void UPlayerItemData::SetItemCount(bool IsPlusMinus)
{
	if (IsPlusMinus)
	{
		ItemCount++;
	}

	else
	{
		ItemCount--;
	}
}

void UPlayerItemData::SetItemImage(UTexture2D* setImage)
{
	ItemImage = setImage;
}

int UPlayerItemData::GetItemCount()
{
	return ItemCount;
}

int UPlayerItemData::GetItemIndex()
{
	return ItemIndex;
}

FString UPlayerItemData::GetItemName()
{
	return ItemName;
}

UTexture2D* UPlayerItemData::GetItemImage()
{
	return ItemImage;
}

FString UPlayerItemData::GetItemDescript()
{
	return ItemDescript;
}

FString UPlayerItemData::GetItemType()
{
	return ItemType;
}

FString UPlayerItemData::GetItemID()
{
	return ItemID;
}