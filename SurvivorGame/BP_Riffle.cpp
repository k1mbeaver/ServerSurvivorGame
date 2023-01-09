// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Riffle.h"
#include "GunAnimInstance.h"
#include "Engine/SkeletalMesh.h"
#include "MyGameInstance.h"

// Sets default values
ABP_Riffle::ABP_Riffle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	GunSkeletalMesh->SetupAttachment(RootComponent);

	nCurrentBullet = 30;
	nDefaultBullet = 30;
}

// Called when the game starts or when spawned
void ABP_Riffle::BeginPlay()
{
	Super::BeginPlay();

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	GunSkeletalMesh->SetSkeletalMesh(MyGameInstance->GetItemSkeletalMesh("1"));
}

// Called every frame
void ABP_Riffle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABP_Riffle::OnFire()
{
	MyGunAnimInstance->IsFire = true;
}

void ABP_Riffle::OnReload()
{
	MyGunAnimInstance->IsReload = true;
}

void ABP_Riffle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABP_Riffle, nCurrentBullet);
	DOREPLIFETIME(ABP_Riffle, nDefaultBullet);

}