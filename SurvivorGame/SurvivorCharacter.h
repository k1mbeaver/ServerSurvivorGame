
// Fill out your copyright notice in the Description page of Project Settings.
// #include "ItemDataStruct.h"
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "SurvivorCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FHitDamage_HitDelegate); // 피격

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

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = HiddenMision)
		bool bCanBasicAttack;

	class UMyGameInstance* myGameInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleInstanceOnly, Category = Animation)
		class UPlayerAnimInstance* CharacterAnim;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = Weapon)
		class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ASurvivorGameProjectile> ProjectileClass;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = Projectile)
		FVector GunOffset;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Mesh)
		USceneComponent* MuzzleLocation;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		EWeaponState CurrentWeaponState;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Run)
		float fCurrentPawnSpeed;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Run)
		float fSprintPawnSpeed;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Crouch)
		float fCrouchingPawnSpeed;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Direction)
		bool IsRight;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Projectile)
		int nProjectileMagazine;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Projectile)
		int nDefaultMagazine;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Projectile)
		int nCurrentMagazine;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Gun)
		FString GunName;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Gun)
		FString GunItemID;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Player)
		EPlayerState CurrentPlayerState;

	UPROPERTY(EditAnyWhere, Replicated, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float PlayerHP;

	UPROPERTY(EditAnyWhere, Replicated, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float PlayerDefaultHP;

	UPROPERTY(EditAnyWhere, Replicated, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float PlayerStamina;

	UPROPERTY(EditAnyWhere, Replicated, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float PlayerDefaultStamina;

	UPROPERTY(EditAnyWhere, Replicated, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bHasGun = false;

	UPROPERTY(EditAnyWhere, Replicated, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bCanGetItem;

	UPROPERTY(EditAnyWhere, Replicated, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bPlayerGet;

	UPROPERTY(EditAnyWhere, Replicated, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		class UObject* NearItem;

	UPROPERTY(EditAnyWhere, Replicated, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bCanFire = true;

	//UPROPERTY(EditAnyWhere, Replicated, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		//FItemData ItemData;

	FHitDamage_HitDelegate HitDamage_Hit;

public:

	// 이벤트
	UFUNCTION(BlueprintNativeEvent)
		void OnWeaponEquip();
	virtual void OnWeaponEquip_Implementation()
	{

	}

	// 이벤트
	UFUNCTION(BlueprintNativeEvent)
		void OnGetItem();
	virtual void OnGetItem_Implementation()
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

	UFUNCTION(BlueprintCallable)
		void SetDead();

	UFUNCTION(BlueprintCallable)
		void GetDamage(float fDamage);

	UFUNCTION(BlueprintCallable)
		TSubclassOf<class ASurvivorGameProjectile> GetProjectileClass();

	UFUNCTION(BlueprintCallable)
		void WeaponUIManage();

	UFUNCTION(BlueprintCallable)
		void PlayerHasGun();

	UFUNCTION(BlueprintCallable)
		void PlayerCantGetItem();

	UFUNCTION(BlueprintCallable)
		void SetCanGetItem();

	UFUNCTION(BlueprintCallable)
		void SetNearItem(UObject* objNearItem);

	UFUNCTION(BlueprintCallable)
		void InitNearItem();

	UFUNCTION(BlueprintCallable)
		void InitGun(int GunMagazine);

	//UFUNCTION(BlueprintCallable)
		//void GetItemData(FItemData GetItemData);

	UFUNCTION(BlueprintCallable)
		void GetItemData(int DefaultMagazine, bool IsWeapon, FString ItemName, FString ItemID, UStaticMesh* ItemStaticMesh);

	// 함수
	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	void GoRightOrLeft();

	void StopRightOrLeft();

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);

	void Run();

	void StopRun();

	virtual void Jump() override;
	
	virtual void StopJumping() override;

	UFUNCTION(BlueprintCallable)
		void GetItem();

	void EquipGun();

	void Crouching();

	void StopCrouching();

	void Punching();

	void OnFire();

	void PlayerAttack();

	void ToAim();

	void EndAim();

	void Reload();

	void ReloadEnd();

	void WeaponUIVisible();

	void WeaponUIHidden();
};