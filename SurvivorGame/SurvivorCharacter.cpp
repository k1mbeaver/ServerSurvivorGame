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
#include "MyGameMode.h"

// Sets default values
ASurvivorCharacter::ASurvivorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	WeaponMesh->SetupAttachment(GetCapsuleComponent());

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
	CharacterAnim->PlayFireMontage();
	OnEventFire();
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
	OnEventReload();
}

void ASurvivorCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASurvivorCharacter, bCanRun);
	DOREPLIFETIME(ASurvivorCharacter, bCanCrouching);
	DOREPLIFETIME(ASurvivorCharacter, fCurrentPawnSpeed);
	DOREPLIFETIME(ASurvivorCharacter, fSprintPawnSpeed);
	DOREPLIFETIME(ASurvivorCharacter, WeaponMesh);
	DOREPLIFETIME(ASurvivorCharacter, bCanBasicAttack);
	DOREPLIFETIME(ASurvivorCharacter, bCanGetItem);
}