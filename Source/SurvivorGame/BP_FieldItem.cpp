// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_FieldItem.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MyGameInstance.h"
#include "PlayerItemData.h"

// Sets default values
ABP_FieldItem::ABP_FieldItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ItemStaticMesh->SetupAttachment(RootComponent);

	//bIsWeapon = false;
	//nDefaultBullet = 0;
	//ItemSkeletalMesh = NULL;
	//ItemName = "";
}

// Called when the game starts or when spawned
void ABP_FieldItem::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

	if (MyGI->GetItemEquipType(ItemID) == "Weapon")
	{
		bIsWeapon = true;
		nDefaultBullet = MyGI->GetProjectileMagazine(MyGI->GetItemName(ItemID));
		ItemStatic = MyGI->GetItemStaticMesh(ItemID);
		ItemName = MyGI->GetItemName(ItemID);
		ItemStaticMesh->SetStaticMesh(MyGI->GetItemStaticMesh(ItemID));
	}

	else
	{
		bIsWeapon = false;
		ItemName = MyGI->GetItemName(ItemID);
		ItemStaticMesh->SetStaticMesh(MyGI->GetItemStaticMesh(ItemID));
	}
}

// Called every frame
void ABP_FieldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ABP_FieldItem::GetDefaultBullet()
{
	return nDefaultBullet;
}

FString ABP_FieldItem::GetItemID()
{
	return ItemID;
}

FString ABP_FieldItem::GetItemName()
{
	return ItemName;
}

UStaticMesh* ABP_FieldItem::GetItemStaticMesh()
{
	return ItemStaticMesh->GetStaticMesh();
		//MyGameInstance->GetItemStaticMesh(ItemID);
}

USkeletalMesh* ABP_FieldItem::GetItemSkeletalMesh()
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

	return MyGI->GetItemSkeletalMesh(ItemID);
	//MyGameInstance->GetItemStaticMesh(ItemID);
}

bool ABP_FieldItem::GetIsWeapon()
{
	return bIsWeapon;
}

UPlayerItemData* ABP_FieldItem::GetPlayerItemData()
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	UPlayerItemData* ItemData = NewObject<UPlayerItemData>(this, UPlayerItemData::StaticClass());;
	ItemData->SetItemCount(1);
	ItemData->SetItemName(MyGI->GetItemName(ItemID));
	ItemData->SetItemID(ItemID);
	ItemData->SetItemImage(MyGI->GetItemImage(ItemID));
	ItemData->SetItemType(MyGI->GetItemEquipType(ItemID));
	return ItemData;
}

void ABP_FieldItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABP_FieldItem, nDefaultBullet);
	DOREPLIFETIME(ABP_FieldItem, ItemID);
	DOREPLIFETIME(ABP_FieldItem, ItemName);
	DOREPLIFETIME(ABP_FieldItem, bIsWeapon);
	DOREPLIFETIME(ABP_FieldItem, ItemStaticMesh);
	DOREPLIFETIME(ABP_FieldItem, ItemStatic);
}