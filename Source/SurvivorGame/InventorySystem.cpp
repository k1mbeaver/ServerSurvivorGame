// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"

void UInventorySystem::AddItem(UPlayerItemData* Item)
{
    if (InventoryItems.Contains(Item))
    {
        Item->ItemCount++; //-> �̰� �������� ������ ������Ų��.
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
        Item->ItemCount--; //-> �̰� �������� ������ ���ҽ�Ų��.

        if (Item->ItemCount == 0) // ���� �������� ���� 0�� �Ǹ� ����
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