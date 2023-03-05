// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_FieldItem.h"
#include "ItemSpawner.generated.h"

UCLASS()
class SURVIVORGAME_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<ABP_FieldItem>> ItemClasses;

	UPROPERTY(EditAnywhere)
		int NumItemsToSpawn;

	UPROPERTY(EditAnywhere)
		float SpawnRadius;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnItems();
	int RandomItem();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
