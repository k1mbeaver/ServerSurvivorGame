// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "PlayerMainUI.h"

APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UPlayerMainUI> WB_Main(TEXT("WidgetBlueprint'/Game/WIdget/PlayerMainUI'"));
	if (WB_Main.Succeeded())
	{
		MainUIClass = WB_Main.Class;
	}
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject(); // �����ϸ� UI�� �����Ѵ�.
}

bool APlayerHUD::CheckUIObject()
{
	if (MainUIObject == nullptr) // UI�� ���ٸ� ����.
	{
		return CreateUIObject();
	}
	return true; // �ִٸ� True.
}

bool APlayerHUD::CreateUIObject()
{
	if (MainUIClass)
	{
		MainUIObject = CreateWidget<UPlayerMainUI>(GetOwningPlayerController(), MainUIClass);
		if (MainUIObject)
		{
			MainUIObject->AddToViewport();
			return true; // ������ٸ� true.
		}
	}
	return false; // �� ������ٸ� false.
}

void APlayerHUD::SetHealthPersent(float PlayerHP)
{
	MainUIObject->SetHealthPersent(PlayerHP);
}

void APlayerHUD::SetStaminaPersent(float PlayerStamina)
{
	MainUIObject->SetStaminaPersent(PlayerStamina);
}

void APlayerHUD::SetImage(UTexture2D* CurrentImage)
{
	MainUIObject->SetImage(CurrentImage);
}

void APlayerHUD::SetImageUse()
{
	MainUIObject->SetImageUse();
}

void APlayerHUD::SetImageNotUse()
{
	MainUIObject->SetImageNotUse();
}

void APlayerHUD::SetImageVisible()
{
	MainUIObject->SetImageVisible();
}

void APlayerHUD::SetImageHidden()
{
	MainUIObject->SetImageHidden();
}

void APlayerHUD::SetProjectileText(int nProjectile)
{
	MainUIObject->SetProjectileText(nProjectile);
}

void APlayerHUD::SetDefaultText(int nProjectile)
{
	MainUIObject->SetDefaultText(nProjectile);
}