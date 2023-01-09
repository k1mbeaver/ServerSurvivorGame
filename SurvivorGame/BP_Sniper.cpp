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

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	GunSkeletalMesh->SetupAttachment(RootComponent);

	nCurrentBullet = 5;
	nDefaultBullet = 5;
}

// Called when the game starts or when spawned
void ABP_Sniper::BeginPlay()
{
	Super::BeginPlay();
	
	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	GunSkeletalMesh->SetSkeletalMesh(MyGameInstance->GetItemSkeletalMesh("2"));
}

// Called every frame
void ABP_Sniper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABP_Sniper::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABP_Sniper, nCurrentBullet);
	DOREPLIFETIME(ABP_Sniper, nDefaultBullet);
}
