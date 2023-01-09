// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "BP_Riffle.generated.h"

UCLASS()
class SURVIVORGAME_API ABP_Riffle : public AActor
{
	GENERATED_BODY()
	
private:
	class UGunAnimInstance* MyGunAnimInstance;
	class UMyGameInstance* MyGameInstance;

public:	
	// Sets default values for this actor's properties
	ABP_Riffle();

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

	UFUNCTION(BlueprintCallable)
		void OnFire();

	UFUNCTION(BlueprintCallable)
		void OnReload();
};
