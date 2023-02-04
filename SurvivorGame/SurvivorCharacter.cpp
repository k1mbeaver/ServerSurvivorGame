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

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// ĳ���Ͱ� �ڿ������� ȸ���ϰ� 
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
	PlayerHP = 200.0f;

	GunOffset = FVector(200.0f, 0.0f, 10.0f);

	nProjectileMagazine = 0; // �Ҹ��� źâ
	nDefaultMagazine = 0; // ���Ե� ���� ����Ʈ �Ѿ� ���� ��) ������ = 5��, ������ = 30��
	nCurrentMagazine = 0; // ���� �����ϰ� �ִ� �Ѿ��� ����

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

	// ����ٰ� �������� MuzzleLocation ���� ���ͼ� ��������
	MuzzleLocation->SetRelativeLocation(myGameInstance->GetParticleMuzzleLocation("1"));
	MuzzleLocation->SetRelativeRotation(FRotator(0.0f, -270.0f, 0.0f));
	GunOffset = myGameInstance->GetParticleMuzzleLocation("1");

	// AnimNotify
	//CharacterAnim->ReloadEnd_Reload.AddUObject(this, &ASurvivorCharacter::ReloadEnd);

	// �׽�Ʈ �����Դϴ�
	CharacterAnim->IsFire = true;
	nProjectileMagazine = 30;
	nCurrentMagazine = 30;
	CurrentWeaponState = EWeaponState::SHOOT;
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

void ASurvivorCharacter::UpDown(float NewAxisValue)
{
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
	CharacterAnim->CurrentLeftRight = 0;
}

void ASurvivorCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void ASurvivorCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

void ASurvivorCharacter::Run()
{
	if (bCanRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = fSprintPawnSpeed;
		bCanCrouching = false;
	}
}


void ASurvivorCharacter::StopRun()
{
	if (bCanRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = fCurrentPawnSpeed;
		bCanCrouching = true;
	}
}

void ASurvivorCharacter::Jump()
{
	Super::Jump();
}

void ASurvivorCharacter::StopJumping()
{
	Super::StopJumping();
}

void ASurvivorCharacter::GetItem()
{
	if (CurrentWeaponState == EWeaponState::PUNCH)
	{
		CurrentWeaponState = EWeaponState::SHOOT;
		CharacterAnim->IsFire = true;

		nProjectileMagazine = myGameInstance->GetProjectileMagazine("Riffle");
		nDefaultMagazine = myGameInstance->GetProjectileMagazine("Riffle");

		// nCurrentMagazine ���߿� ź ������ ȹ���� �� ����ٰ� �߰�

		OnWeaponEquip();
	}

	else
	{
		CurrentWeaponState = EWeaponState::PUNCH;
		CharacterAnim->IsFire = false;
	}
}

void ASurvivorCharacter::SetCanGetItem()
{
	if (bCanGetItem)
	{
		bCanGetItem = false;
	}

	else
	{
		bCanGetItem = true;
	}
}

TSubclassOf<class ASurvivorGameProjectile> ASurvivorCharacter::GetProjectileClass()
{
	return ProjectileClass;
}

void ASurvivorCharacter::Crouching()
{
	if (bCanCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = fCrouchingPawnSpeed;
		CharacterAnim->IsCrouching = true;
		bCanRun = false;
	}
}

void ASurvivorCharacter::StopCrouching()
{
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
	if (nProjectileMagazine < 1)
	{
		return;
	}

	// ź���� ������ ���δ�.
	nProjectileMagazine--;

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
	GameStatic->SpawnEmitterAttached(myGameInstance->GetParticle("Riffle"), MuzzleLocation, FName("MuzzleLocation"));

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ProjectileStart!!"));
	//OnEventFire(); // �̺�Ʈ�� �޾Ƽ� �������Ʈ���� �� �߻��ϴ°� ����
}

void ASurvivorCharacter::PlayerAttack()
{
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
	Camera->SetRelativeLocation(FVector(450.0f, 0.0f, 50.0f));
}

void ASurvivorCharacter::EndAim()
{
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
}

void ASurvivorCharacter::Reload()
{
	if (nCurrentMagazine <= 0) // ���� �������� �ش� �Ѿ��� ������ 0���� ������
	{
		return;
	}

	OnEventReload();

	CharacterAnim->PlayReloadMontage();
}

void ASurvivorCharacter::ReloadEnd()
{
	if (nCurrentMagazine < nDefaultMagazine) // 
	{
		nProjectileMagazine = nCurrentMagazine;

		nCurrentMagazine = 0;
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ReloadEnd!!"));


	nCurrentMagazine = nCurrentMagazine - nDefaultMagazine;
	nProjectileMagazine = 30; // nDefaultMagazine ���߿� UI �۾��� �� ���� ����
}

void ASurvivorCharacter::SetDead()
{
	CharacterAnim->SetDeadAnim();
}

void ASurvivorCharacter::GetDamage(float fDamage)
{
	PlayerHP = PlayerHP - fDamage;

	if (PlayerHP <= 0)
	{
		SetDead();
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
}