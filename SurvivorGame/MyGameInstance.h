// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

struct FItemDataTable;

class UDataTable;
/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();

	FString GetItemName(FString ItemID);
	FString GetItemEquipType(FString ItemID);
	USkeletalMesh* GetItemSkeletalMesh(FString ItemID);

private:
	UPROPERTY()
		UDataTable* FItemFileTable;
};
