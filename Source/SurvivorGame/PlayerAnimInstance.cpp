// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	CurrentLeftRight = 0.0f;
	IsInAir = false;
	IsDead = false;
	IsAttacking = false;
	IsBack = false;
	IsCrouching = false;
	IsFire = false;
	IsReload = false;
	IsHit = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/Animation/fbx/CrossPunch4UE4_Montage.CrossPunch4UE4_Montage'"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		PunchMontage = ATTACK_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FIRE_MONTAGE(TEXT("AnimMontage'/Game/Animation/fbx/RIfleFire4UE4_Montage.RIfleFire4UE4_Montage'"));
	if (FIRE_MONTAGE.Succeeded())
	{
		FireMontage = FIRE_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> RELOAD_MONTAGE(TEXT("AnimMontage'/Game/Animation/fbx/Reloading4UE4_Montage.Reloading4UE4_Montage'"));
	if (RELOAD_MONTAGE.Succeeded())
	{
		ReloadMontage = RELOAD_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HIT_MONTAGE(TEXT("AnimMontage'/Game/Animation/fbx/HitReaction4UE4_Montage.HitReaction4UE4_Montage'"));
	if (HIT_MONTAGE.Succeeded())
	{
		HitMontage = HIT_MONTAGE.Object;
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // 폰에 접근해서 폰의 속력 값을 얻어온다.
	if (!::IsValid(Pawn)) return;

	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	Montage_Play(PunchMontage, 1.0f);
}

void UPlayerAnimInstance::PlayFireMontage()
{
	Montage_Play(FireMontage, 2.0f);
}

void UPlayerAnimInstance::PlayReloadMontage()
{
	Montage_Play(ReloadMontage, 1.0f);
}

void UPlayerAnimInstance::PlayHitMontage()
{
	Montage_Play(HitMontage, 1.0f);
}

void UPlayerAnimInstance::SetDeadAnim()
{
	IsDead = true;
}

void UPlayerAnimInstance::AnimNotify_ReloadEnd()
{
	ReloadEnd_Reload.Broadcast();
}