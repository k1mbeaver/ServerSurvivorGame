// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UPlayerInventoryUI : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(Meta = (BindWidget))
		class UListView* myListView;

	UPROPERTY(Meta = (BindWidget))
		class UImage* WeaponImage;

	UPROPERTY(Meta = (BindWidget))
		class UInventoryItemDescriptUI* MyInventoryItemDescript;

private:
	TArray<UPlayerItemData*> InventoryItemsData;
	FString CurrentHoverItemID;
protected:
	virtual void NativeOnInitialized() override;

public:
	//void SetImage(UTexture2D* Image);
	//void SetName(FString strName);
	//void SetDescript(FString strDescript);
	void SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage);
	void SetHidden();
	void SetVisible();
	void SetListCount(int nIndex, int nCount);
	void SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage);
	void SetWeaponImage(UTexture2D* setImage);
	void SetInventoryArray(TArray<UPlayerItemData*> getInventoryArray);

	UFUNCTION(BlueprintCallable)
		void SetDescriptVisible();

	UFUNCTION(BlueprintCallable)
		void SetDescriptHidden();

	UFUNCTION(BlueprintCallable)
		void SetDescriptItem(int getItemIndex);

	UFUNCTION(BlueprintCallable)
		void SetCurrentHoverItemID(FString ItemID);

	UFUNCTION(BlueprintCallable)
		void UseItem();

	UFUNCTION(BlueprintCallable)
		FString GetCurrentHoverItemID();

	UFUNCTION(BlueprintCallable)
		TArray<UPlayerItemData*> GetInventoryArray();

	UFUNCTION(BlueprintCallable)
		UPlayerItemData* CastUPlayerItemData(UObject* getObject);

	void ListUpdate();
	void Init();
};
