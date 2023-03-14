// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(meta = (BindWidget))
        class UTextBlock* ItemName;

    UPROPERTY(meta = (BindWidget))
        class UImage* ItemImage;

    UPROPERTY(meta = (BindWidget))
        class UTextBlock* ItemCount;

    UFUNCTION()
        void OnItemClicked();

    void SetItemImage(UTexture2D* ItemImage);
    void SetItemCount(int nCount);
    void SetItemName(FString ItemName);
    
    UFUNCTION(BlueprintCallable)
        void SetData(class UPlayerItemData* Data);

    UFUNCTION(BlueprintCallable)
        UPlayerItemData* CastToPlayerItemData(UObject* ListItemObject);

protected:
    virtual void NativeOnInitialized() override;
};
