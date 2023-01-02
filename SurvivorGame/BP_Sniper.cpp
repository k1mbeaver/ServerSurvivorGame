// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Sniper.h"
#include "GunAnimInstance.h"
#include "Engine/SkeletalMesh.h"
#include "MyGameInstance.h"

// Sets default values
ABP_Sniper::ABP_Sniper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABP_Sniper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABP_Sniper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

