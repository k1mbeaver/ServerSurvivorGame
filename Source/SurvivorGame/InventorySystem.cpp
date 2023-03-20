// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"

void UInventorySystem::AddItem(UPlayerItemData* Item)
{
    if (InventoryItems.Contains(Item))
    {
        Item->ItemCount++; //-> 이건 아이템의 수량을 증가시킨다.
    }
    else
    {
        InventoryItems.Add(Item);
        Item->SetItemIndex(InventoryItems.Num());
    }
}

void UInventorySystem::RemoveItem(UPlayerItemData* Item)
{
    if (InventoryItems.Contains(Item))
    {
        Item->ItemCount--; //-> 이건 아이템의 수량을 감소시킨다.

        if (Item->ItemCount == 0) // 만약 아이템의 수가 0가 되면 삭제
        {
            InventoryItems.Remove(Item);
        }
    }
}

int UInventorySystem::GetInventorySize()
{
    return InventoryItems.Num();
}

void UInventorySystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventorySystem, InventoryItems);

}