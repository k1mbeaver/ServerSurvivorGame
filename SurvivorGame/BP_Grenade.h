// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Grenade.generated.h"

UCLASS()
class SURVIVORGAME_API ABP_Grenade : public AActor
{
	GENERATED_BODY()

private:
	//UPROPERTY(VisibleInstanceOnly, Replicated, Category = ItemID)
		//FString ItemID = "3";
	
public:	
	// Sets default values for this actor's properties
	ABP_Grenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
