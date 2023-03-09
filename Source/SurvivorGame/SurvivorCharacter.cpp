// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.h"
#include "Survivor_PC.h"
#include "MyGameInstance.h"
#include "SurvivorGameProjectile.h"
#include "PlayerHUD.h"
#include "MyGameMode.h"

// Sets default values
ASurvivorCharacter::ASurvivorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	WeaponMesh->SetupAttachment(GetCapsuleComponent());

	MuzzleLocation->SetupAttachment(WeaponMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	MuzzleLocation->SetRelativeRotation(FRotator(0.0f, -270.0f, 0.0f));

	WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "RightHand_Weapon");

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// 캐릭터가 자연스럽게 회전하게 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	bCanRun = true;
	bCanCrouching = true;
	bCanBasicAttack = true;
	bCanGetItem = false;
	IsRight = true;

	fCurrentPawnSpeed = 200.0f;
	fSprintPawnSpeed = 400.0f;
	fCrouchingPawnSpeed = 100.0f;
	//PlayerHP = 200.0f;
	PlayerDefaultHP = 200.0f;
	PlayerStamina = 100.0f;
	PlayerDefaultStamina = 100.0f;

	GunOffset = FVector(200.0f, 0.0f, 10.0f);

	nProjectileMagazine = 0; // 소모할 탄창
	nDefaultMagazine = 0; // 갖게될 총의 디폴트 총알 갯수 예) 저격총 = 5발, 라이플 = 30발
	nCurrentMagazine = 200; // 현재 소유하고 있는 총알의 갯수

	CurrentPlayerState = EPlayerState::ALIVE;
	CurrentWeaponState = EWeaponState::PUNCH;
}

// Called when the game starts or when spawned
void ASurvivorCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	myGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	CharacterAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	GetMesh()->SetSkeletalMesh(myGameInstance->GetPlayerSkeletalMesh("1"));

	// 여기다가 아이템의 MuzzleLocation 값을 얻어와서 적용하자
	MuzzleLocation->SetRelativeLocation(myGameInstance->GetParticleMuzzleLocation("1"));
	MuzzleLocation->SetRelativeRotation(FRotator(0.0f, -270.0f, 0.0f));
	GunOffset = myGameInstance->GetParticleMuzzleLocation("1");

	// AnimNotify
	CharacterAnim->ReloadEnd_Reload.AddUObject(this, &ASurvivorCharacter::ReloadEnd);

	PlayerHP = myGameInstance->GetPlayerCurrentHP("1");

	//MyPlayerController = Cast<ASurvivor_PC>(GetOwner()->GetInstigatorController());

	// 테스트 전용입니다
	//CharacterAnim->IsFire = true;
	//nProjectileMagazine = 30;
	//nCurrentMagazine = 30;
	//CurrentWeaponState = EWeaponState::SHOOT;
}

// Called every frame
void ASurvivorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASurvivorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/*
void ASurvivorCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	MyPlayerController = Cast<ASurvivor_PC>(NewController);
}
*/

void ASurvivorCharacter::UpDown(float NewAxisValue)
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);
	
	Direction.Z = 0.0f;
	Direction.Normalize();

	if (NewAxisValue < 0)
	{
		CharacterAnim->IsBack = true;
	}

	else
	{
		CharacterAnim->IsBack = false;
	}
	
	AddMovementInput(Direction, NewAxisValue);
}

void ASurvivorCharacter::LeftRight(float NewAxisValue)
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);

	Direction.Z = 0.0f;
	Direction.Normalize();
	
	if (NewAxisValue > 0)
	{
		IsRight = true;
	}

	else
	{
		IsRight = false;
	}
	
	AddMovementInput(Direction, NewAxisValue);
}

void ASurvivorCharacter::GoRightOrLeft()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	if (IsRight == true)
	{
		CharacterAnim->CurrentLeftRight = 1.0f;
	}

	else
	{
		CharacterAnim->CurrentLeftRight = -1.0f;
	}
}

void ASurvivorCharacter::StopRightOrLeft()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	CharacterAnim->CurrentLeftRight = 0;
}

void ASurvivorCharacter::LookUp(float NewAxisValue)
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	AddControllerPitchInput(NewAxisValue);
}

void ASurvivorCharacter::Turn(float NewAxisValue)
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	AddControllerYawInput(NewAxisValue);
}

void ASurvivorCharacter::Run()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	if (bCanRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = fSprintPawnSpeed;
		bCanCrouching = false;
	}
}


void ASurvivorCharacter::StopRun()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	if (bCanRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = fCurrentPawnSpeed;
		bCanCrouching = true;
	}
}

void ASurvivorCharacter::Jump()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	Super::Jump();
}

void ASurvivorCharacter::StopJumping()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	Super::StopJumping();
}

void ASurvivorCharacter::GetItem()
{
	// 2/14 나중에 E 버튼을 눌렀을 때 아이템을 획득하게 이 함수에서는 1. 총 발사준비, 2. 총 내려놓기 두가지로 분류

	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	if (bCanGetItem)
	{
		OnGetItem();
		bPlayerGet = true;
	}
}

void ASurvivorCharacter::SetCanGetItem()
{
	bCanGetItem = true;
}

void ASurvivorCharacter::PlayerCantGetItem()
{
	bCanGetItem = false;
}

void ASurvivorCharacter::SetNearItem(AActor* objNearItem)
{
	NearItem = objNearItem;
}

void ASurvivorCharacter::InitNearItem()
{
	NearItem = NULL;
}

void ASurvivorCharacter::EquipGun()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	//if (!bHasGun)
	//{
		//return;
	//}

	if (CurrentWeaponState == EWeaponState::PUNCH)
	{
		CurrentWeaponState = EWeaponState::SHOOT;
		CharacterAnim->IsFire = true;

		myGameInstance->SetPlayerCurrentWeapon("1", GunName);
		WeaponMesh->SetSkeletalMesh(GunSkeletalMesh);

		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("GetItem!!"));
		// nCurrentMagazine 나중에 탄 아이템 획득할 때 여기다가 추가
	}

	else
	{
		CurrentWeaponState = EWeaponState::PUNCH;
		myGameInstance->SetPlayerCurrentWeapon("1", "Punch");
		CharacterAnim->IsFire = false;
	}
}


void ASurvivorCharacter::GetItemData(bool IsWeapon, FString ItemID)
{
	if (IsWeapon)
	{
		//UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
		GunItemID = ItemID;
		GunName = myGameInstance->GetItemName(GunItemID);
		GunSkeletalMesh = myGameInstance->GetItemSkeletalMesh(GunItemID);
		InitGun(myGameInstance->GetProjectileMagazine(GunName));
		return;
	}
}

void ASurvivorCharacter::HealthCharacter(FString ItemID)
{
	if (myGameInstance->GetItemEquipType(ItemID) == "HpItem")
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("GetHPItem!!"));
		HealthHP();
		return;
	}

	else if (myGameInstance->GetItemEquipType(ItemID) == "StaminaItem")
	{
		HealthStamina();
		return;
	}
}

float ASurvivorCharacter::GetHP()
{
	return this->PlayerHP;
		//myGameInstance->GetPlayerCurrentHP("1");
		//this->PlayerHP;
}

void ASurvivorCharacter::SetHP(float newHP)
{
	//myGameInstance->SetPlayerCurrentHP("1", newHP);

	//FString MyString = FString::SanitizeFloat(myGameInstance->GetPlayerCurrentHP("1"));

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, *MyString);
	this->PlayerHP = newHP;
	return;
}

void ASurvivorCharacter::HealthHP()
{
	float myHP = GetHP();
	myHP = myHP + 20.0f; // 이건 나중에 수정하자
	SetHP(myHP);

		//myGameInstance->GetItemHealthPercent(ItemID);

	//if (!MyPlayerController)
	//{
		//return;
	//}

	//ASurvivor_PC* myPlayerController = Cast<ASurvivor_PC>(UGameplayStatics::GetPlayerController(this, 0));
	MyPlayerController->GetHealthHUD(GetHP());
}

void ASurvivorCharacter::HealthStamina()
{
	//this->PlayerStamina = myStamina + myGameInstance->GetItemHealthPercent(ItemID);

	if (!MyPlayerController)
	{
		return;
	}

	//ASurvivor_PC* myPlayerController = Cast<ASurvivor_PC>(UGameplayStatics::GetPlayerController(this, 0));
	//MyPlayerController->GetHealthHUD();
}

void ASurvivorCharacter::InitGun(int GunMagazine)
{
	nProjectileMagazine = GunMagazine;
	nDefaultMagazine = GunMagazine;

	MuzzleLocation->SetRelativeLocation(myGameInstance->GetParticleMuzzleLocation(GunItemID));
	MuzzleLocation->SetRelativeRotation(FRotator(0.0f, -270.0f, 0.0f));
	GunOffset = myGameInstance->GetParticleMuzzleLocation(GunItemID);
}

TSubclassOf<class ASurvivorGameProjectile> ASurvivorCharacter::GetProjectileClass()
{
	return ProjectileClass;
}

void ASurvivorCharacter::Crouching()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	if (bCanCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = fCrouchingPawnSpeed;
		CharacterAnim->IsCrouching = true;
		bCanRun = false;
	}
}

void ASurvivorCharacter::StopCrouching()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	if (bCanCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = fCurrentPawnSpeed;
		CharacterAnim->IsCrouching = false;
		bCanRun = true;
	}
}

void ASurvivorCharacter::Punching()
{
	CharacterAnim->PlayAttackMontage();
}

void ASurvivorCharacter::OnFire()
{
	if (bCanFire)
	{
		// try and fire a projectile
		if (ProjectileClass != nullptr)
		{
			UWorld* const World = GetWorld();

			if (World != nullptr)
			{
				/*
				if (bUsingMotionControllers)
				{
					const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
					const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
					World->SpawnActor<ASurvivorGameProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
				}
				*/

				const FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
				//((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentRotation() : GetActorRotation());
				//GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = MuzzleLocation->GetComponentLocation();
				//((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation());
			//  + SpawnRotation.RotateVector(GunOffset)

			//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<ASurvivorGameProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}

		CharacterAnim->PlayFireMontage();
		GameStatic->SpawnEmitterAttached(myGameInstance->GetParticle(GunName), MuzzleLocation, FName("MuzzleLocation"));

		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ProjectileStart!!"));
		//OnEventFire(); // 이벤트를 받아서 블루프린트에서 총 발사하는거 설정
	}
}

void ASurvivorCharacter::PlayerAttack()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	if (CurrentWeaponState == EWeaponState::SHOOT)
	{
		OnFire();
	}

	else if (CurrentWeaponState == EWeaponState::PUNCH)
	{
		Punching();
	}
}

void ASurvivorCharacter::ToAim()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	Camera->SetRelativeLocation(FVector(450.0f, 0.0f, 50.0f));
}

void ASurvivorCharacter::EndAim()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
}

void ASurvivorCharacter::Reload()
{
	if (CurrentPlayerState == EPlayerState::DEAD)
	{
		return;
	}

	if (nCurrentMagazine <= 0) // 현재 소유중인 해당 총알의 갯수가 0보다 작으면
	{
		return;
	}

	/*
	if (nCurrentMagazine < nDefaultMagazine) // 
	{
		nProjectileMagazine = nCurrentMagazine;

		nCurrentMagazine = 0;
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ReloadEnd!!"));


	nCurrentMagazine = nCurrentMagazine - nProjectileMagazine;
	nProjectileMagazine = 30; // nDefaultMagazine 나중에 UI 작업할 때 같이 편집
	*/
	CharacterAnim->PlayReloadMontage();
	bCanFire = false;
}

void ASurvivorCharacter::ReloadEnd()
{
	bCanFire = true;
}

void ASurvivorCharacter::SetDead()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("PlayerDead!!"));
	CharacterAnim->SetDeadAnim();

	this->CurrentPlayerState = EPlayerState::DEAD;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
}

void ASurvivorCharacter::GetDamage(float fDamage)
{
	float myHp = GetHP();
	myHp = myHp - fDamage;
	SetHP(myHp);

	CharacterAnim->PlayHitMontage();

	if (myHp <= 0)
	{
		SetDead();
	}

	if (!MyPlayerController)
	{
		return;
	}

	//HitDamage_Hit.Broadcast();
	// 2/15 현재 한 캐릭터가 데미지를 입으면 모든 캐릭터들이 데미지를 입는것으로 UI의 체력이 깎임
	//ASurvivor_PC* myPlayerController = Cast<ASurvivor_PC>(UGameplayStatics::GetPlayerController(this, 0));
	MyPlayerController->GetDamageHUD();

	//myPlayerController->GetDamageHUD(this->PlayerHP / this->PlayerDefaultHP);

	//APlayerHUD* HUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	//HUD->SetHealthPersent(this->PlayerHP / this->PlayerDefaultHP);	
}

void ASurvivorCharacter::WeaponUIVisible()
{
	if (!MyPlayerController)
	{
		return;
	}

	MyPlayerController->WeaponUIVisible();
}

void ASurvivorCharacter::WeaponUIHidden()
{
	if (!MyPlayerController)
	{
		return;
	}

	MyPlayerController->WeaponUIHidden();
}

void ASurvivorCharacter::WeaponUIManage()
{
	if (CurrentWeaponState == EWeaponState::PUNCH)
	{
		WeaponUIHidden();
	}

	else if (CurrentWeaponState == EWeaponState::SHOOT)
	{
		WeaponUIVisible();
	}
}

void ASurvivorCharacter::PlayerHasGun()
{
	if (bHasGun)
	{
		bHasGun = false;
	}

	else
	{
		bHasGun = true;
	}
}


void ASurvivorCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASurvivorCharacter, bCanRun);
	DOREPLIFETIME(ASurvivorCharacter, bCanCrouching);
	DOREPLIFETIME(ASurvivorCharacter, fCurrentPawnSpeed);
	DOREPLIFETIME(ASurvivorCharacter, fSprintPawnSpeed);
	DOREPLIFETIME(ASurvivorCharacter, WeaponMesh);
	DOREPLIFETIME(ASurvivorCharacter, MuzzleLocation);
	DOREPLIFETIME(ASurvivorCharacter, GunOffset);
	DOREPLIFETIME(ASurvivorCharacter, bCanBasicAttack);
	DOREPLIFETIME(ASurvivorCharacter, bCanGetItem);
	DOREPLIFETIME(ASurvivorCharacter, nCurrentMagazine);
	DOREPLIFETIME(ASurvivorCharacter, nDefaultMagazine);
	DOREPLIFETIME(ASurvivorCharacter, nProjectileMagazine);
	DOREPLIFETIME(ASurvivorCharacter, PlayerHP);
	DOREPLIFETIME(ASurvivorCharacter, PlayerStamina);
	DOREPLIFETIME(ASurvivorCharacter, PlayerDefaultHP);
	DOREPLIFETIME(ASurvivorCharacter, PlayerDefaultStamina);
	DOREPLIFETIME(ASurvivorCharacter, CurrentPlayerState);
	DOREPLIFETIME(ASurvivorCharacter, bHasGun);
	DOREPLIFETIME(ASurvivorCharacter, GunName);
	DOREPLIFETIME(ASurvivorCharacter, GunItemID);
	DOREPLIFETIME(ASurvivorCharacter, GunSkeletalMesh);
	DOREPLIFETIME(ASurvivorCharacter, MyPlayerController);
}