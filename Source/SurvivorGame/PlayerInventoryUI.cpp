// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "PlayerItemData.h"
#include "InventorySystem.h"
#include "MyGameInstance.h"
#include "InventoryItemDescriptUI.h"
#include "InventoryItemWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Survivor_PC.h"

void UPlayerInventoryUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	myListView = Cast<UListView>(GetWidgetFromName(TEXT("myListView")));
	WeaponImage = Cast<UImage>(GetWidgetFromName(TEXT("WeaponImage")));
	MyInventoryItemDescript = Cast<UInventoryItemDescriptUI>(GetWidgetFromName(TEXT("MyInventoryItemDescript")));
}

void UPlayerInventoryUI::SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	UPlayerItemData* ItemData = Cast<UPlayerItemData>(myListView->GetItemAt(nIndex));

	ItemData->SetItemName(strName);
	ItemData->SetItemCount(true);
	ItemData->SetItemImage(setImage);
}

void UPlayerInventoryUI::SetHidden()
{
	Init();
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerInventoryUI::SetVisible()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UPlayerInventoryUI::ListUpdate()
{
	//myListView->RegenerateAllEntries();
	myListView->ClearListItems();
	InventoryItemsData.Empty();
}

void UPlayerInventoryUI::SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();

	UPlayerItemData* ItemData = NewObject<UPlayerItemData>(this, UPlayerItemData::StaticClass());
	ItemData->SetItemIndex(nIndex);
	ItemData->SetItemCountSet(nCount);
	ItemData->SetItemName(strName);
	ItemData->SetItemImage(setImage);

	myListView->AddItem(ItemData);
	InventoryItemsData.Add(ItemData);
}

void UPlayerInventoryUI::SetListCount(int nIndex, int nCount)
{
	UPlayerItemData* ItemData = Cast<UPlayerItemData>(myListView->GetItemAt(nIndex));

	ItemData->SetItemCount(true);
}

void UPlayerInventoryUI::Init()
{
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();

	//ItemImage->SetBrushFromTexture(MyGI->GetItemImage("5"));
	//ItemName->SetText(FText::FromString(""));
	//ItemDescript->SetText(FText::FromString(""));
}

void UPlayerInventoryUI::SetWeaponImage(UTexture2D* setImage)
{
	WeaponImage->SetBrushFromTexture(setImage);
}

void UPlayerInventoryUI::SetDescriptVisible()
{
	MyInventoryItemDescript->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerInventoryUI::SetDescriptHidden()
{
	MyInventoryItemDescript->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerInventoryUI::SetDescriptItem(int getItemIndex)
{
	FString strItemIndex = FString::FromInt(getItemIndex);
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();

	MyInventoryItemDescript->SetItemImage(MyGI->GetInventoryImage(getItemIndex + 1));
	MyInventoryItemDescript->SetItemName(MyGI->GetInventoryItemName(getItemIndex + 1));
	MyInventoryItemDescript->SetItemDescript(MyGI->GetInventoryItemDescript(getItemIndex + 1));

	SetCurrentHoverItemID(MyGI->GetInventoryItemID(getItemIndex + 1));
}


TArray<UPlayerItemData*> UPlayerInventoryUI::GetInventoryArray()
{
	return InventoryItemsData;
}

void UPlayerInventoryUI::SetInventoryArray(TArray<UPlayerItemData*> getInventoryArray)
{
	InventoryItemsData = getInventoryArray;
}

UPlayerItemData* UPlayerInventoryUI::CastUPlayerItemData(UObject* getObject)
{
	UPlayerItemData* CastObj = Cast<UPlayerItemData>(getObject);

	return CastObj;
}

FString UPlayerInventoryUI::GetCurrentHoverItemID()
{
	return CurrentHoverItemID;
}

void UPlayerInventoryUI::SetCurrentHoverItemID(FString ItemID)
{
	CurrentHoverItemID = ItemID;
}

void UPlayerInventoryUI::UseItem()
{
	ASurvivor_PC* MyPC = Cast<ASurvivor_PC>(UGameplayStatics::GetPlayerController(this, 0));
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();

	MyPC->GetHealthHUD(MyGI->GetItemHealthPercent(CurrentHoverItemID));

	return;
}