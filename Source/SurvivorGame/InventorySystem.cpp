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