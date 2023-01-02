// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "ItemDataTableClass.h"

UMyGameInstance::UMyGameInstance()
{
	FString ItemFileDataPath = TEXT("DataTable'/Game/DataTable/ItemDataTable.ItemDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYITEMFILE(*ItemFileDataPath);

	if (DT_MYITEMFILE.Succeeded())
	{
		FItemFileTable = DT_MYITEMFILE.Object;
	}
}

FString UMyGameInstance::GetItemName(FString ItemID)
{
	FItemDataTable* ItemData = FItemFileTable->FindRow<FItemDataTable>(*ItemID, TEXT(""));
	FString ItemName = ItemData->ItemName;
	return ItemName;
}

FString UMyGameInstance::GetItemEquipType(FString ItemID)
{
	FItemDataTable* ItemData = FItemFileTable->FindRow<FItemDataTable>(*ItemID, TEXT(""));
	FString ItemEquipType = ItemData->ItemEquipType;
	return ItemEquipType;
}

USkeletalMesh* UMyGameInstance::GetItemSkeletalMesh(FString ItemID)
{
	FItemDataTable* ItemData = FItemFileTable->FindRow<FItemDataTable>(*ItemID, TEXT(""));
	USkeletalMesh* ItemSkeletalMesh = ItemData->ItemSkeletalMesh;
	return ItemSkeletalMesh;
}