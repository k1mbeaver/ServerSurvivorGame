// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "PlayerDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FPlayerDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* CurrentPlayerSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PlayerKill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PlayerDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PlayerCurrentWalk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PlayerCurrentRun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PlayerCurrentCrouchWalk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PlayerCurrentWeapon;
};
UCLASS()
class SURVIVORGAME_API APlayerDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
