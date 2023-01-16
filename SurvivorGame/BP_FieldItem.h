// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "BP_FieldItem.generated.h"

UCLASS()
class SURVIVORGAME_API ABP_FieldItem : public AActor
{
	GENERATED_BODY()
	
private:
	class UMyGameInstance* MyGameInstance;

	//UPROPERTY(VisibleInstanceOnly, Replicated, Category = ItemID)
		//FString ItemID;

public:
	// Sets default values for this actor's properties
	ABP_FieldItem();

	class USkeletalMeshComponent* ItemSkeletalMesh;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Gun)
		int nCurrentBullet;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Gun)
		int nDefaultBullet;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
