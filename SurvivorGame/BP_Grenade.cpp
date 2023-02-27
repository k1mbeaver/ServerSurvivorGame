// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Grenade.h"
#include "GunAnimInstance.h"
#include "Engine/SkeletalMesh.h"
#include "MyGameInstance.h"

// Sets default values
ABP_Grenade::ABP_Grenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABP_Grenade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABP_Grenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

