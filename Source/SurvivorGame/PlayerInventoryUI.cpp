// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "PlayerItemData.h"
#include "InventorySystem.h"
#include "MyGameInstance.h"

void UPlayerInventoryUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	myListView = Cast<UListView>(GetWidgetFromName(TEXT("myListView")));
}

void UPlayerInventoryUI::SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	UPlayerItemData* ItemData = Cast<UPlayerItemData>(myListView->GetItemAt(nIndex));

	ItemData->SetItemName(strName);
	ItemData->SetItemCount(nCount);
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
	myListView->RegenerateAllEntries();
}

void UPlayerInventoryUI::SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();

	UPlayerItemData* ItemData = NewObject<UPlayerItemData>(this, UPlayerItemData::StaticClass());
	ItemData->SetItemIndex(nIndex);
	ItemData->SetItemCount(0);
	ItemData->SetItemName("Test");
	ItemData->SetItemImage(MyGI->GetItemImage("5"));
	myListView->AddItem(ItemData);
}

void UPlayerInventoryUI::SetListCount(int nIndex, int nCount)
{
	UPlayerItemData* ItemData = Cast<UPlayerItemData>(myListView->GetItemAt(nIndex));

	ItemData->SetItemCount(nCount);
}

void UPlayerInventoryUI::Init()
{
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();

	//ItemImage->SetBrushFromTexture(MyGI->GetItemImage("5"));
	//ItemName->SetText(FText::FromString(""));
	//ItemDescript->SetText(FText::FromString(""));
}