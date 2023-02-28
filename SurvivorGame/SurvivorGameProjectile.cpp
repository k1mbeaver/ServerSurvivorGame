
// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurvivorGameProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SurvivorCharacter.h"
#include "MyGameInstance.h"

ASurvivorGameProjectile::ASurvivorGameProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ASurvivorGameProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	ProjectileStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 5000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ASurvivorGameProjectile::BeginPlay()
{
	Super::BeginPlay();

	myGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	ProjectileName = myGameInstance->GetPlayerCurrentWeapon("1");

	if (ProjectileName == "Punch")
	{
		return;
	}

	ProjectilePower = myGameInstance->GetProjectilePower(ProjectileName);
	ProjectileSpeed = myGameInstance->GetProjectileSpeed(ProjectileName);

	ProjectileMovement->MaxSpeed = ProjectileSpeed;
}

void ASurvivorGameProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	/*
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();
	ProjectilePower = MyGI->GetProjectilePower("1");

	if (Cast<ASurvivorCharacter>(OtherActor))
	{
		ASurvivorCharacter* HitCharacter = Cast<ASurvivorCharacter>(Hit.Actor);

		HitCharacter->GetDamage(ProjectilePower);

		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ProjectileDestroy!!"));
		Destroy();
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ProjectileDestroy!!"));
		Destroy();
	}
	
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ProjectileDestroy!!"));

		Destroy();
	}
	*/
}

float ASurvivorGameProjectile::GetBulletDamage()
{
	return ProjectilePower;
}