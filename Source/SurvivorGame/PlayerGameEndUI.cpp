// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameEndUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UPlayerGameEndUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtExit = Cast<UButton>(GetWidgetFromName(TEXT("BtExit")));
	TextWin = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextWin")));
}

void UPlayerGameEndUI::SetHidden()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerGameEndUI::SetVisible()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UPlayerGameEndUI::SetWin()
{
	FString myString = "YOU WIN!";
	FText myText = FText::FromString(myString);
	TextWin->SetText(myText);
}

void UPlayerGameEndUI::SetLose()
{
	FString myString = "YOU DEAD!";
	FText myText = FText::FromString(myString);
	TextWin->SetText(myText);
}