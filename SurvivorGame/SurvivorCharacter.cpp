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

	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// 캐릭터가 자연스럽게 회전하게 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	bCanRun = true;
	bCanCrouching = true;

	fCurrentPawnSpeed = 200.0f;
	fSprintPawnSpeed = 400.0f;

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

	// 캐릭터 이동 함수
	//InputComponent->BindAxis(TEXT("MoveForward"), this, &ASurvivorCharacter::UpDown);
	//InputComponent->BindAxis(TEXT("MoveRight"), this, &ASurvivorCharacter::LeftRight);
	//InputComponent->BindAxis(TEXT("LookUp"), this, &ASurvivorCharacter::LookUp);
	//InputComponent->BindAxis(TEXT("Turn"), this, &ASurvivorCharacter::Turn);

	// 캐릭터 달리기
	//InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &ASurvivorCharacter::Run);
	//InputComponent->BindAction(TEXT("Run"), IE_Released, this, &ASurvivorCharacter::StopRun);

	// 캐릭터 점프
	//InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ASurvivorCharacter::Jump);
	//InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ASurvivorCharacter::StopJumping);

	// 캐릭터 앉기
	//InputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &ASurvivorCharacter::Crouching);
	//InputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &ASurvivorCharacter::StopCrouching);

	// 캐릭터 아이템 얻기
	//InputComponent->BindAction(TEXT("ItemGet"), IE_Pressed, this, &ASurvivorCharacter::GetItem);

	// 캐릭터 공격
	//InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ASurvivorCharacter::PlayerAttack);

	// 캐릭터 장전
	//InputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &ASurvivorCharacter::Reload);

	// 캐릭터 견착
	//InputComponent->BindAction(TEXT("Aim"), IE_Pressed, this, &ASurvivorCharacter::ToAim);
	//InputComponent->BindAction(TEXT("Aim"), IE_Released, this, &ASurvivorCharacter::EndAim);
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

	AddMovementInput(Direction, NewAxisValue);
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

void ASurvivorCharacter::Crouching()
{
	if (bCanCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed /= 2;
		CharacterAnim->IsCrouching = true;
		bCanRun = false;
	}
}

void ASurvivorCharacter::StopCrouching()
{
	if (bCanCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed *= 2;
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
}