// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"

void UInventorySystem::AddItem(ABP_FieldItem* Item)
{
    if (InventoryItems.Contains(Item))
    {
        //Item->Quantity++; -> �̰� �������� ������ ������Ų��.
    }
    else
    {
        InventoryItems.Add(Item);
    }
}

void UInventorySystem::RemoveItem(ABP_FieldItem* Item)
{
    if (InventoryItems.Contains(Item))
    {
        // Item->Quantity--; -> �̰� �������� ������ ���ҽ�Ų��.

        //if (Item->Quantity == 0) // ���� �������� ���� 0�� �Ǹ� ����
        //{
            //InventoryItems.Remove(Item);
        //}
    }
}