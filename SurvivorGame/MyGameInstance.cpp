// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "ItemDataTableClass.h"
#include "PlayerDataTableClass.h"
#include "ParticleDataTableClass.h"
#include "ProjectileDataTableClass.h"

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

USkeletalMesh* UMyGameInstance::GetItemSkeletalMesh(FString ItemID)
{
	FItemDataTable* ItemData = FItemFileTable->FindRow<FItemDataTable>(*ItemID, TEXT(""));
	USkeletalMesh* ItemSkeletalMesh = ItemData->ItemSkeletalMesh;
	return ItemSkeletalMesh;
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