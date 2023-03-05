// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"
#include "NavigationSystem.h"
#include "random"
// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
    SpawnItems();
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpawner::SpawnItems()
{
    for (int i = 0; i < NumItemsToSpawn; i++)
    {
        // Get a random reachable location within the spawn radius
        FVector SpawnLocation;

        UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

        //int ItemIndex = FMath::RandRange(0, ItemClasses.Num() - 1);
        int ItemIndex = RandomItem();
        TSubclassOf<ABP_FieldItem> ItemClass = ItemClasses[ItemIndex];

        if (NavSystem && NavSystem->GetMainNavData())
        {
            FNavLocation RandomNavLocation;
            NavSystem->GetRandomReachablePointInRadius(GetActorLocation(), SpawnRadius, RandomNavLocation);
            SpawnLocation = RandomNavLocation.Location;
        }

        // Spawn the item at the chosen location
        //AActor* SpawnedItem = GetWorld()->SpawnActor(ItemClass, &SpawnLocation);
        GetWorld()->SpawnActor(ItemClass, &SpawnLocation);
    }
}

int AItemSpawner::RandomItem()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, ItemClasses.Num() - 1);

    int random_num = dist(gen);

    return random_num;
}