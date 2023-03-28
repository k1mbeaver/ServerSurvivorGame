
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

struct FItemDataTable;
struct FPlayerDataTable;
struct FParticleDataTable;
struct FProjectileDataTable;
struct FInventoryDataTable;

class UDataTable;
/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();

	// 아이템 값 얻어오기
	FString GetItemName(FString ItemID);
	FString GetItemEquipType(FString ItemID);
	FString GetItemDescript(FString ItemID);
	FVector GetParticleMuzzleLocation(FString ItemID);
	UTexture2D* GetItemImage(FString ItemID);
	UStaticMesh* GetItemStaticMesh(FString ItemID);
	USkeletalMesh* GetItemSkeletalMesh(FString ItemID);
	float GetItemHealthPercent(FString ItemID);

	// 캐릭터 값 얻어오기
	FString GetPlayerName(FString PlayerID);
	int GetPlayerKill(FString PlayerID);
	int GetPlayerDeath(FString PlayerID);
	FString GetPlayerCurrentWeapon(FString PlayerID);
	void SetPlayerName(FString PlayerID, FString PlayerName);
	void SetPlayerKill(FString PlayerID, int PlayerKill);
	void SetPlayerDeath(FString PlayerID, int PlayerDeath);
	void SetPlayerCurrentWeapon(FString PlayerID, FString WeaponName);
	USkeletalMesh* GetPlayerSkeletalMesh(FString PlayerID);
	void SetPlayerSkeletalMesh(FString PlayerID, USkeletalMesh* PlayerSkeletalMesh);
	float GetPlayerCurrentHP(FString PlayerID);
	void SetPlayerCurrentHP(FString PlayerID, float PlayerCurrentHP);
	float GetPlayerCurrentStamina(FString PlayerID);
	void SetPlayerCurrentStamina(FString PlayerID, float PlayerCurrentStamina);

	// 파티클 값 얻어오기

	UParticleSystem* GetParticle(FString ParticleID);

	// Projectile 값 얻어오기

	UStaticMesh* GetProjectileStaticMesh(FString ProjectileID);
	float GetProjectilePower(FString ProjectileID);
	float GetProjectileSpeed(FString ProjectileID);
	int GetProjectileMagazine(FString ProjectileID);

	// 인벤토리 값 얻어오기

	UTexture2D* GetInventoryImage(int ItemIndex);
	int GetInventoryCount(int ItemIndex);
	FString GetInventoryItemID(int ItemIndex);
	FString GetInventoryItemName(int ItemIndex);
	FString GetInventoryItemEquipType(int ItemIndex);
	FString GetInventoryItemDescript(int ItemIndex);

	void SetInventoryItemImage(int ItemIndex, UTexture2D* ItemImage);
	void SetInventoryItemCount(int ItemIndex, int ItemCount);
	void SetInventoryItemID(int ItemIndex, FString ItemID);
	void SetInventoryItemName(int ItemIndex, FString ItemName);
	void SetInventoryItemEquipType(int ItemIndex, FString ItemEquipType);
	void SetInventoryItemDescript(int ItemIndex, FString ItemDescript);

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemEquipType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ItemImage;
	*/


private:
	UPROPERTY()
		UDataTable* FItemFileTable;

	UPROPERTY()
		UDataTable* FPlayerFileTable;

	UPROPERTY()
		UDataTable* FParticleFileTable;

	UPROPERTY()
		UDataTable* FProjectileFileTable;

	UPROPERTY()
		UDataTable* FInventoryFileTable;
};