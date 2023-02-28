// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_FieldItem.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MyGameInstance.h"

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

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (MyGameInstance->GetItemEquipType(ItemID) == "Weapon")
	{
		bIsWeapon = true;
		nDefaultBullet = MyGameInstance->GetProjectileMagazine(MyGameInstance->GetItemName(ItemID));
		ItemStatic = MyGameInstance->GetItemStaticMesh(ItemID);
		ItemName = MyGameInstance->GetItemName(ItemID);
		ItemStaticMesh->SetStaticMesh(MyGameInstance->GetItemStaticMesh(ItemID));
	}

	else
	{
		bIsWeapon = false;
		ItemName = MyGameInstance->GetItemName(ItemID);
		ItemStaticMesh->SetStaticMesh(MyGameInstance->GetItemStaticMesh(ItemID));
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
	return MyGameInstance->GetItemStaticMesh(ItemID);
}

bool ABP_FieldItem::GetIsWeapon()
{
	return bIsWeapon;
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