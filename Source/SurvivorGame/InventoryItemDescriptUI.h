// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemDescriptUI.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UInventoryItemDescriptUI : public UUserWidget
{
	GENERATED_BODY()
	
		UPROPERTY(Meta = (BindWidget))
		class UImage* ItemImage;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemName;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemDescript;

protected:
	virtual void NativeOnInitialized() override;

public:
	void SetItemImage(UTexture2D* myItemImage);
	void SetItemName(FString myItemName);
	void SetItemDescript(FString myItemDescript);
};
