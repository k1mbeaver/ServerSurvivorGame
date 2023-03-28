// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UInventorySystem::AddItem(UPlayerItemData* Item)
{
    //InventoryItems.Contains(Item)
    for (int nIndex = 0; nIndex < InventoryItems.Num(); nIndex++)
    {
        if (InventoryItems[nIndex]->GetItemID() == Item->GetItemID())
        {
            InventoryItems[nIndex]->SetItemCount(true); //-> 이건 아이템의 수량을 증가시킨다.

            UMyGameInstance* MyGI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

            MyGI->SetInventoryItemCount(InventoryItems[nIndex]->GetItemIndex(), InventoryItems[nIndex]->GetItemCount());
            return;
        }
    }

    InventoryItems.Add(Item);
    Item->SetItemIndex(InventoryItems.Num());

    UMyGameInstance* MyGI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    MyGI->SetInventoryItemCount(Item->GetItemIndex(), Item->GetItemCount());
    MyGI->SetInventoryItemID(Item->GetItemIndex(), Item->GetItemID());
    MyGI->SetInventoryItemName(Item->GetItemIndex(), Item->GetItemName());
    MyGI->SetInventoryItemImage(Item->GetItemIndex(), Item->GetItemImage());
    MyGI->SetInventoryItemEquipType(Item->GetItemIndex(), Item->GetItemType());
    MyGI->SetInventoryItemDescript(Item->GetItemIndex(), Item->GetItemDescript());

    /*
    if (InventoryItems.Contains(Item))
    {
        Item->SetItemCount(true); //-> 이건 아이템의 수량을 증가시킨다.

        UMyGameInstance* MyGI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

        MyGI->SetInventoryItemCount(Item->GetItemIndex(), Item->GetItemCount());
    }
    */
}

void UInventorySystem::RemoveItem(UPlayerItemData* Item)
{
    for (int nIndex = 0; nIndex < InventoryItems.Num(); nIndex++)
    {
        if (InventoryItems[nIndex]->GetItemID() == Item->GetItemID())
        {
            Item->SetItemCount(false); //-> 이건 아이템의 수량을 감소시킨다.

            UMyGameInstance* MyGI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

            MyGI->SetInventoryItemCount(Item->GetItemIndex(), Item->GetItemCount());

            if (Item->GetItemCount() == 0) // 만약 아이템의 수가 0가 되면 삭제
            {
                InventoryItems.Remove(Item);

                MyGI->SetInventoryItemCount(Item->GetItemIndex(), 0);
                MyGI->SetInventoryItemID(Item->GetItemIndex(), "");
                MyGI->SetInventoryItemName(Item->GetItemIndex(), "");
                MyGI->SetInventoryItemImage(Item->GetItemIndex(), MyGI->GetItemImage("5"));
                MyGI->SetInventoryItemEquipType(Item->GetItemIndex(), "");
                MyGI->SetInventoryItemDescript(Item->GetItemIndex(), "");
            }
            return;
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