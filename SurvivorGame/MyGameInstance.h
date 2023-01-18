// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

struct FItemDataTable;
struct FPlayerDataTable;
struct FParticleDataTable;

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

	// ������ �� ������
	FString GetItemName(FString ItemID);
	FString GetItemEquipType(FString ItemID);
	USkeletalMesh* GetItemSkeletalMesh(FString ItemID);

	// ĳ���� �� ������
	FString GetPlayerName(FString PlayerID);
	int GetPlayerKill(FString PlayerID);
	int GetPlayerDeath(FString PlayerID);
	void SetPlayerName(FString PlayerID, FString PlayerName);
	void SetPlayerKill(FString PlayerID, int PlayerKill);
	void SetPlayerDeath(FString PlayerID, int PlayerDeath);
	USkeletalMesh* GetPlayerSkeletalMesh(FString PlayerID);
	void SetPlayerSkeletalMesh(FString PlayerID, USkeletalMesh* PlayerSkeletalMesh);

	// ��ƼŬ �� ������

	UParticleSystem* GetParticle(FString ParticleID);

private:
	UPROPERTY()
		UDataTable* FItemFileTable;

	UPROPERTY()
		UDataTable* FPlayerFileTable;

	UPROPERTY()
		UDataTable* FParticleFileTable;
};
