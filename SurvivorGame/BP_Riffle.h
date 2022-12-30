// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Riffle.generated.h"

UCLASS()
class SURVIVORGAME_API ABP_Riffle : public AActor
{
	GENERATED_BODY()
	
private:
	class UGunAnimInstance* MyGunAnimInstance;
public:	
	// Sets default values for this actor's properties
	ABP_Riffle();

	class USkeletalMeshComponent* GunSkeletalMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void OnFire();

	UFUNCTION(BlueprintCallable)
		void OnReload();
};
