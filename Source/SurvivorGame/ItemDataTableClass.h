
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FItemDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemClassID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemEquipType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* ItemStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector ParticleMuzzleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ItemHealthPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* ItemSkeletalMesh;
};

UCLASS()
class SURVIVORGAME_API AItemDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};