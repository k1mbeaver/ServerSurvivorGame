// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ProjectileDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FProjectileDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ProjectilePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ProjectileMagazine;
};

UCLASS()
class SURVIVORGAME_API AProjectileDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
