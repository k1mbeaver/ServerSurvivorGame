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
	void ListUpdate();
	void Init();
};
