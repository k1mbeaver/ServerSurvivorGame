// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerItemData.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UPlayerItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ItemCount;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		int ItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		FString ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		FString ItemID;

public:
	void SetItemIndex(int nIndex);
	void SetItemName(FString strName);
	void SetItemImage(UTexture2D* setImage);
	void SetItemCount(int nCount);
	void SetItemDescript(FString strDescript);
	void SetItemType(FString strItemType);
	void SetItemID(FString strItemID);

	int GetItemIndex();
	int GetItemCount();
	FString GetItemName();
	UTexture2D* GetItemImage();
	FString GetItemDescript();
	FString GetItemType();
	FString GetItemID();

	FString ItemDescript;
};
