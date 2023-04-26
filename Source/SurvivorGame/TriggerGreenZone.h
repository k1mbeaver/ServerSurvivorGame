// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "Net/UnrealNetwork.h"
#include "TriggerGreenZone.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API ATriggerGreenZone : public ATriggerSphere
{
	GENERATED_BODY()
	
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

private:
	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Radius)
	float fGreenZoneRadius;

public:
};
