// Fill out your copyright notice in the Description page of Project Settings.


#include "GunAnimInstance.h"

UGunAnimInstance::UGunAnimInstance()
{
	IsFire = false;
	IsReload = false;

	/*
	static ConstructorHelpers::FObjectFinder<UAnimMontage> FIRE_MONTAGE(TEXT("AnimMontage'/Game/Animation/fbx/MmaKick4UE4_Montage.MmaKick4UE4_Montage'"));
	if (FIRE_MONTAGE.Succeeded())
	{
		FireMontage = FIRE_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> RELOAD_MONTAGE(TEXT("AnimMontage'/Game/Animation/fbx/RIfleFire4UE4_Montage.RIfleFire4UE4_Montage'"));
	if (RELOAD_MONTAGE.Succeeded())
	{
		ReloadMontage = RELOAD_MONTAGE.Object;
	}
	*/
}

/*
void UGunAnimInstance::PlayFireMontage()
{
	Montage_Play(FireMontage, 1.0f);
}

void UGunAnimInstance::PlayReloadMontage()
{
	Montage_Play(ReloadMontage, 2.0f);
}
*/

void UGunAnimInstance::AnimNotify_OnGunReload()
{
	OnGunReload.Broadcast();
}

void UGunAnimInstance::AnimNotify_OnGunReloadInsert()
{
	OnGunReloadInsert.Broadcast();
	IsReload = false;
}

void UGunAnimInstance::AnimNotify_OnGunFire()
{
	OnGunFire.Broadcast();
}

void UGunAnimInstance::AnimNotify_OnGunFireEnd()
{
	OnGunFireEnd.Broadcast();
	IsFire = false;
}