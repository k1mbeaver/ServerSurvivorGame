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

    UPROPERTY(Meta = (BindWidget))
        class UImage* bgImage;

    UFUNCTION(BlueprintCallable)
        void OnItemClicked();

    UFUNCTION(BlueprintCallable)
        void PlayerHover();

    UFUNCTION(BlueprintCallable)
        void PlayerHoverEnd();

    void SetItemImage(UTexture2D* ItemImage);
    void SetItemCount(int nCount);
    void SetItemName(FString ItemName);
    
    UFUNCTION(BlueprintCallable)
        void SetData(class UPlayerItemData* Data);

    UFUNCTION(BlueprintCallable)
        UPlayerItemData* CastToPlayerItemData(UObject* ListItemObject);

    UFUNCTION(BlueprintCallable)
        FString GetItemID();

private:
    class UPlayerItemData* myData;

    FLinearColor HoverColor = FLinearColor(0.7f, 0.7f, 0.7f, 0.5f);
    FLinearColor HoverEndColor = FLinearColor(0.5f, 0.5f, 0.5f, 0.5f);
    FLinearColor SelectColor = FLinearColor(0.2f, 0.2f, 0.2f, 0.5f);
    //FLinearColor Default Color;

protected:
    virtual void NativeOnInitialized() override;
};
