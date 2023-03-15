// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerItemData.h"
#include "InventorySystem.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UInventorySystem : public UObject
{
	GENERATED_BODY()
	
public:
	TArray<UPlayerItemData*> InventoryItems;

	void AddItem(UPlayerItemData* Item);
	void RemoveItem(UPlayerItemData* Item);
	int GetInventorySize();
};
