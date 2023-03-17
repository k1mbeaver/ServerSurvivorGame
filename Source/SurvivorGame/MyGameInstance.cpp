// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "ItemDataTableClass.h"
#include "PlayerDataTableClass.h"
#include "ParticleDataTableClass.h"
#include "ProjectileDataTableClass.h"
#include "InventoryDataTableClass.h"

UMyGameInstance::UMyGameInstance()
{
	FString ItemFileDataPath = TEXT("DataTable'/Game/DataTable/ItemDataTable.ItemDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYITEMFILE(*ItemFileDataPath);

	if (DT_MYITEMFILE.Succeeded())
	{
		FItemFileTable = DT_MYITEMFILE.Object;
	}

	FString PlayerFileDataPath = TEXT("DataTable'/Game/DataTable/PlayerDataTable.PlayerDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYPLAYERFILE(*PlayerFileDataPath);

	if (DT_MYPLAYERFILE.Succeeded())
	{
		FPlayerFileTable = DT_MYPLAYERFILE.Object;
	}

	FString ParticleFileDataPath = TEXT("DataTable'/Game/DataTable/ParticleDataTable.ParticleDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYPARTICLEFILE(*ParticleFileDataPath);

	if (DT_MYPARTICLEFILE.Succeeded())
	{
		FParticleFileTable = DT_MYPARTICLEFILE.Object;
	}

	FString ProjectileFileDataPath = TEXT("DataTable'/Game/DataTable/ProjectileDataTable.ProjectileDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYPROJECTILEFILE(*ProjectileFileDataPath);

	if (DT_MYPROJECTILEFILE.Succeeded())
	{
		FProjectileFileTable = DT_MYPROJECTILEFILE.Object;
	}

	FString InventoryFileDataPath = TEXT("DataTable'/Game/DataTable/InventoryDataTable.InventoryDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYINVENTORYFILE(*InventoryFileDataPath);

	if (DT_MYINVENTORYFILE.Succeeded())
	{
		FInventoryFileTable = DT_MYINVENTORYFILE.Object;
	}
}

FString UMyGameInstance::GetItemName(FString ItemID)
{
	FItemDataTable* ItemData = FItemFileTable->FindRow<FItemDataTable>(*ItemID, TEXT(""));
	FString ItemName = ItemData->ItemName;
	return ItemName;
}

FString UMyGameInstance::GetItemEquipType(FString ItemID)
{
	FItemDataTable* ItemData = FItemFileTable->FindRow<FItemDataTable>(*ItemID, TEXT(""));
	FString ItemEquipType = ItemData->ItemEquipType;
	return ItemEquipType;
}

UStaticMesh* UMyGameInstance::GetItemStaticMesh(FString ItemID)
{
	FItemDataTable* ItemData = FItemFileTable->FindRow<FItemDataTable>(*ItemID, TEXT(""));
	UStaticMesh* ItemStaticMesh = ItemData->ItemStaticMesh;
	return ItemStaticMesh;
}

USkeletalMesh* UMyGameInstance::GetItemSkeletalMesh(FString ItemID)
{
	FItemDataTable* ItemData = FItemFileTable->FindRow<FItemDataTable>(*ItemID, TEXT(""));
	USkeletalMesh* ItemSkeletalMesh = ItemData->ItemSkeletalMesh;
	return ItemSkeletalMesh;
}

float UMyGameInstance::GetItemHealthPercent(FString ItemID)
{
	FItemDataTable* ItemData = FItemFileTable->FindRow<FItemDataTable>(*ItemID, TEXT(""));
	float ItemHealthPercent = ItemData->ItemHealthPercent;
	return ItemHealthPercent;
}

UTexture2D* UMyGameInstance::GetItemImage(FString ItemID)
{
	FItemDataTable* ItemData = FItemFileTable->FindRow<FItemDataTable>(*ItemID, TEXT(""));
	UTexture2D* ItemImage = ItemData->ItemImage;
	return ItemImage;
}

FVector UMyGameInstance::GetParticleMuzzleLocation(FString ItemID)
{
	FItemDataTable* ItemData = FItemFileTable->FindRow<FItemDataTable>(*ItemID, TEXT(""));
	FVector ParticleMuzzleLocation = ItemData->ParticleMuzzleLocation;
	return ParticleMuzzleLocation;
}

FString UMyGameInstance::GetPlayerName(FString PlayerID)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	FString PlayerName = PlayerData->PlayerName;
	return PlayerName;
}

int UMyGameInstance::GetPlayerKill(FString PlayerID)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	int PlayerKill = PlayerData->PlayerKill;
	return PlayerKill;
}

int UMyGameInstance::GetPlayerDeath(FString PlayerID)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	int PlayerDeath = PlayerData->PlayerDeath;
	return PlayerDeath;
}


USkeletalMesh* UMyGameInstance::GetPlayerSkeletalMesh(FString PlayerID)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	USkeletalMesh* PlayerSkeletalMesh = PlayerData->CurrentPlayerSkeletalMesh;
	return PlayerSkeletalMesh;
}

FString UMyGameInstance::GetPlayerCurrentWeapon(FString PlayerID)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	FString WeaponName = PlayerData->PlayerCurrentWeapon;
	return WeaponName;
}

float UMyGameInstance::GetPlayerCurrentHP(FString PlayerID)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	float CurrentHP = PlayerData->PlayerCurrentHP;
	return CurrentHP;
}

void UMyGameInstance::SetPlayerCurrentHP(FString PlayerID, float PlayerCurrentHP)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	PlayerData->PlayerCurrentHP = PlayerCurrentHP;
}

float UMyGameInstance::GetPlayerCurrentStamina(FString PlayerID)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	float CurrentStamina = PlayerData->PlayerCurrentStamina;
	return CurrentStamina;
}

void UMyGameInstance::SetPlayerCurrentStamina(FString PlayerID, float PlayerCurrentStamina)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	PlayerData->PlayerCurrentStamina = PlayerCurrentStamina;
}

void UMyGameInstance::SetPlayerName(FString PlayerID, FString PlayerName)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	PlayerData->PlayerName = PlayerName;
}

void UMyGameInstance::SetPlayerKill(FString PlayerID, int PlayerKill)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	PlayerData->PlayerKill = PlayerKill;
}

void UMyGameInstance::SetPlayerDeath(FString PlayerID, int PlayerDeath)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	PlayerData->PlayerDeath = PlayerDeath;
}

void UMyGameInstance::SetPlayerCurrentWeapon(FString PlayerID, FString WeaponName)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	PlayerData->PlayerCurrentWeapon = WeaponName;
}

void UMyGameInstance::SetPlayerSkeletalMesh(FString PlayerID, USkeletalMesh* PlayerSkeletalMesh)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerID, TEXT(""));
	PlayerData->CurrentPlayerSkeletalMesh = PlayerSkeletalMesh;
}

UParticleSystem* UMyGameInstance::GetParticle(FString ParticleID)
{
	FParticleDataTable* ParticleData = FParticleFileTable->FindRow<FParticleDataTable>(*ParticleID, TEXT(""));
	UParticleSystem* GetParticleData = ParticleData->MyParticle;
	return GetParticleData;
}

UStaticMesh* UMyGameInstance::GetProjectileStaticMesh(FString ProjectileID)
{
	FProjectileDataTable* ProjectileData = FProjectileFileTable->FindRow<FProjectileDataTable>(*ProjectileID, TEXT(""));
	UStaticMesh* GetProjectileData = ProjectileData->ProjectileMesh;
	return GetProjectileData;
}

float UMyGameInstance::GetProjectilePower(FString ProjectileID)
{
	FProjectileDataTable* ProjectileData = FProjectileFileTable->FindRow<FProjectileDataTable>(*ProjectileID, TEXT(""));
	float GetProjectileData = ProjectileData->ProjectilePower;
	return GetProjectileData;
}

float UMyGameInstance::GetProjectileSpeed(FString ProjectileID)
{
	FProjectileDataTable* ProjectileData = FProjectileFileTable->FindRow<FProjectileDataTable>(*ProjectileID, TEXT(""));
	float GetProjectileData = ProjectileData->ProjectileSpeed;
	return GetProjectileData;
}

int UMyGameInstance::GetProjectileMagazine(FString ProjectileID)
{
	FProjectileDataTable* ProjectileData = FProjectileFileTable->FindRow<FProjectileDataTable>(*ProjectileID, TEXT(""));
	int GetProjectileData = ProjectileData->ProjectileMagazine;
	return GetProjectileData;
}

UTexture2D* UMyGameInstance::GetInventoryImage(int ItemIndex)
{

}

int UMyGameInstance::GetInventoryCount(int ItemIndex)
{

}

FString UMyGameInstance::GetInventoryItemID(int ItemIndex)
{

}

FString UMyGameInstance::GetInventoryItemName(int ItemIndex)
{

}

FString UMyGameInstance::GetInventoryItemEquipType(int ItemIndex)
{

}

void UMyGameInstance::SetInventoryItemImage(int ItemIndex, UTexture2D* ItemImage)
{

}

void UMyGameInstance::SetInventoryItemCount(int ItemIndex, int ItemCount)
{

}

void UMyGameInstance::SetInventoryItemID(int ItemIndex, FString ItemID)
{

}

void UMyGameInstance::SetInventoryItemName(int ItemIndex, FString ItemName)
{

}

void UMyGameInstance::SetInventoryItemEquipType(int ItemIndex, FString ItemEquipType)
{

}