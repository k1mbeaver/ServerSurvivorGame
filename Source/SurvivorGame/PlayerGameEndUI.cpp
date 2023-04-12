// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameEndUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Survivor_PC.h"
#include "Kismet/GameplayStatics.h"

void UPlayerGameEndUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtExit = Cast<UButton>(GetWidgetFromName(TEXT("BtExit")));
	BtPreview = Cast<UButton>(GetWidgetFromName(TEXT("BtPreview")));
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
	TextWin->SetVisibility(ESlateVisibility::Visible);
	BtPreview->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerGameEndUI::SetLose()
{
	FString myString = "YOU DEAD!";
	FText myText = FText::FromString(myString);
	TextWin->SetText(myText);
	TextWin->SetVisibility(ESlateVisibility::Visible);
	BtPreview->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerGameEndUI::StartPreview()
{
	ASurvivor_PC* MyPC = Cast<ASurvivor_PC>(UGameplayStatics::GetPlayerController(this, 0));
	MyPC->DestroyCharacter();
	SetHidden();

	return;
	//MyPC->GetHealthHUD(MyGI->GetItemHealthPercent(CurrentHoverItemID));
}

void UPlayerGameEndUI::SetEsc(bool IsEsc)
{
	if (IsEsc)
	{
		SetVisibility(ESlateVisibility::Visible);
		TextWin->SetVisibility(ESlateVisibility::Hidden);
		BtPreview->SetVisibility(ESlateVisibility::Hidden);
	}

	else
	{
		SetVisibility(ESlateVisibility::Hidden);
		BtPreview->SetVisibility(ESlateVisibility::Hidden);
	}

}