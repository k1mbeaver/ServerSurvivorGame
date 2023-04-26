// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerGreenZone.h"
#include "Components/ShapeComponent.h"

void ATriggerGreenZone::BeginPlay()
{
	//fGreenZoneRadius = GetCollisionComponent()->ShapeBodySetup(4000.0f);
}

void ATriggerGreenZone::Tick(float DeltaTime)
{

}

void ATriggerGreenZone::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATriggerGreenZone, fGreenZoneRadius);
}