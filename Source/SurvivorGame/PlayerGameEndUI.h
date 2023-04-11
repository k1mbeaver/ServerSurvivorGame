// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerGameEndUI.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UPlayerGameEndUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(Meta = (BindWidget))
		class UButton* BtExit;

	UPROPERTY(Meta = (BindWidget))
		class UButton* BtPreview;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextWin;
protected:
	virtual void NativeOnInitialized() override;

public:
	void SetVisible();
	void SetHidden();
	void SetWin();
	void SetLose();

	UFUNCTION(BlueprintCallable)
		void StartPreview();
};
