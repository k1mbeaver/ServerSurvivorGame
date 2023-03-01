
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

struct FItemDataTable;
struct FPlayerDataTable;
struct FParticleDataTable;
struct FProjectileDataTable;

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

	// 파티클 값 얻어오기

	UParticleSystem* GetParticle(FString ParticleID);

	// Projectile 값 얻어오기

	UStaticMesh* GetProjectileStaticMesh(FString ProjectileID);
	float GetProjectilePower(FString ProjectileID);
	float GetProjectileSpeed(FString ProjectileID);
	int GetProjectileMagazine(FString ProjectileID);

private:
	UPROPERTY()
		UDataTable* FItemFileTable;

	UPROPERTY()
		UDataTable* FPlayerFileTable;

	UPROPERTY()
		UDataTable* FParticleFileTable;

	UPROPERTY()
		UDataTable* FProjectileFileTable;
};