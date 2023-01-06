// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "SurvivorCharacter.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	PUNCH, // 맨주먹
	SHOOT, // 총
};

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	ALIVE, // 살아있음
	DEAD, // 죽음(관전)
};

UCLASS()
class SURVIVORGAME_API ASurvivorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASurvivorCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly, Replicated, Category = HiddenMision)
	bool bCanRun;
	UPROPERTY(VisibleInstanceOnly, Replicated, Category = HiddenMision)
	bool bCanCrouching;

	class UMyGameInstance* myGameInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleInstanceOnly, Category = Animation)
		class UPlayerAnimInstance* CharacterAnim;

	UPROPERTY(BlueprintReadWrite, Category = Weapon)
		class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		EPlayerState CurrentPlayerState;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		EWeaponState CurrentWeaponState;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Run)
		float fCurrentPawnSpeed;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Run)
		float fSprintPawnSpeed;

public:

	// 이벤트
	UFUNCTION(BlueprintNativeEvent)
		void OnWeaponEquip();
	virtual void OnWeaponEquip_Implementation()
	{

	}

	UFUNCTION(BlueprintNativeEvent)
		void OnEventFire();
	virtual void OnEventFire_Implementation()
	{

	}

	UFUNCTION(BlueprintNativeEvent)
		void OnEventReload();
	virtual void OnEventReload_Implementation()
	{

	}
	// 함수
	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);

	void Run();

	void StopRun();

	virtual void Jump() override;
	
	virtual void StopJumping() override;

	void GetItem();

	void Crouching();

	void StopCrouching();

	void Punching();

	void OnFire();

	void PlayerAttack();

	void ToAim();

	void EndAim();

	void Reload();
};
