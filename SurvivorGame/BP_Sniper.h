// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "BP_Sniper.generated.h"

UCLASS()
class SURVIVORGAME_API ABP_Sniper : public AActor
{
	GENERATED_BODY()
	
private:
	class UMyGameInstance* MyGameInstance;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = ItemID)
		FString ItemID = "2";
public:	
	// Sets default values for this actor's properties
	ABP_Sniper();

	class USkeletalMeshComponent* GunSkeletalMesh;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Current)
		int nCurrentBullet;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Default)
		int nDefaultBullet;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
