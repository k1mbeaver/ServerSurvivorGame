// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BP_FieldItem.h"
#include "InventorySystem.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UInventorySystem : public UObject
{
	GENERATED_BODY()
	
public:
	TArray<ABP_FieldItem*> InventoryItems;

	void AddItem(ABP_FieldItem* Item);
	void RemoveItem(ABP_FieldItem* Item);
};
