// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_FieldItem.h"
#include "Engine/SkeletalMesh.h"
#include "MyGameInstance.h"

// Sets default values
ABP_FieldItem::ABP_FieldItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	ItemSkeletalMesh->SetupAttachment(RootComponent);

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

	ItemSkeletalMesh->SetSkeletalMesh(MyGameInstance->GetItemSkeletalMesh(ItemID));

	if (MyGameInstance->GetItemEquipType(ItemID) == "Weapon")
	{
		bIsWeapon = true;
		nDefaultBullet = MyGameInstance->GetProjectileMagazine(MyGameInstance->GetItemName(ItemID));
		ItemSkeletal = MyGameInstance->GetItemSkeletalMesh(ItemID);
		ItemName = MyGameInstance->GetItemName(ItemID);
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
	return MyGameInstance->GetItemName(ItemID);
}

USkeletalMesh* ABP_FieldItem::GetSkeletalMesh()
{
	return MyGameInstance->GetItemSkeletalMesh(ItemID);
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
	DOREPLIFETIME(ABP_FieldItem, ItemSkeletal);
	DOREPLIFETIME(ABP_FieldItem, ItemSkeletalMesh);
}

