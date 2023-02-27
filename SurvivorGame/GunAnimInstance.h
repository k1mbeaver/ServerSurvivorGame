// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GunAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnGunReload_ReloadDelegate); // ������ ����
DECLARE_MULTICAST_DELEGATE(FOnGunReloadInsert_ReloadDelegate); // ������ ��
DECLARE_MULTICAST_DELEGATE(FOnGunFire_FireDelegate); // ���� ����
DECLARE_MULTICAST_DELEGATE(FOnGunFireEnd_FireDelegate); // ���� ��

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API UGunAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
		UGunAnimInstance();

public:
	//void PlayFireMontage();
	//void PlayReloadMontage();

public:
	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		//UAnimMontage* FireMontage;

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		//UAnimMontage* ReloadMontage;

private:
	FOnGunReload_ReloadDelegate OnGunReload;
	FOnGunReloadInsert_ReloadDelegate OnGunReloadInsert;
	FOnGunFire_FireDelegate OnGunFire;
	FOnGunFireEnd_FireDelegate OnGunFireEnd;

	UFUNCTION()
		void AnimNotify_OnGunReload();

	UFUNCTION()
		void AnimNotify_OnGunReloadInsert();

	UFUNCTION()
		void AnimNotify_OnGunFire();

	UFUNCTION()
		void AnimNotify_OnGunFireEnd();
public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsFire;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsReload;
};
