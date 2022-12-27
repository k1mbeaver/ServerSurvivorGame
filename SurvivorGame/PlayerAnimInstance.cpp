// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	IsAttacking = false;
	IsBack = false;
	IsCrouching = false;
	IsFire = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/Animation/fbx/Punching4UE4_Montage.Punching4UE4_Montage'"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		PunchMontage = ATTACK_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FIRE_MONTAGE(TEXT("AnimMontage'/Game/Animation/fbx/RIfleFire4UE4_Montage.RIfleFire4UE4_Montage'"));
	if (FIRE_MONTAGE.Succeeded())
	{
		FireMontage = FIRE_MONTAGE.Object;
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
	Montage_Play(FireMontage, 1.0f);
}

void UPlayerAnimInstance::SetDeadAnim()
{
	IsDead = true;
}