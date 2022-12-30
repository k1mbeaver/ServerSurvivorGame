// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Riffle.h"
#include "GunAnimInstance.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
ABP_Riffle::ABP_Riffle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	GunSkeletalMesh->SetupAttachment(RootComponent);
	// 여기는 나중에 GameInstance에서 받아오는거로 교체하자
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_EASYMODEL(TEXT("SkeletalMesh'/Game/MilitaryWeapDark/Weapons/Assault_Rifle_B.Assault_Rifle_B'"));
	if (SK_EASYMODEL.Succeeded())
	{
		GunSkeletalMesh->SetSkeletalMesh(SK_EASYMODEL.Object);
	}

	GunSkeletalMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> GUN_ANIM(TEXT("/Game/Animation/RiffleAnimation.RiffleAnimation_C"));
	if (GUN_ANIM.Succeeded())
	{
		GunSkeletalMesh->SetAnimInstanceClass(GUN_ANIM.Class);
		MyGunAnimInstance = Cast<UGunAnimInstance>(GUN_ANIM.Class);
	}
}

// Called when the game starts or when spawned
void ABP_Riffle::BeginPlay()
{
	Super::BeginPlay();
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
