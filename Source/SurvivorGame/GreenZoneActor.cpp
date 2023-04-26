// Fill out your copyright notice in the Description page of Project Settings.


#include "GreenZoneActor.h"
#include "Components/SphereComponent.h"

// Sets default values
AGreenZoneActor::AGreenZoneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GreenZoneCollision = CreateDefaultSubobject<USphereComponent>(TEXT("GreenZoneCollision"));
}

// Called when the game starts or when spawned
void AGreenZoneActor::BeginPlay()
{
	Super::BeginPlay();

	//GreenZoneCollision->
}
// Called every frame
void AGreenZoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGreenZoneActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGreenZoneActor, CurrentRadius);
}