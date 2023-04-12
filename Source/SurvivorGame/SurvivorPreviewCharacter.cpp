// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorPreviewCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASurvivorPreviewCharacter::ASurvivorPreviewCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void ASurvivorPreviewCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASurvivorPreviewCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASurvivorPreviewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASurvivorPreviewCharacter::UpDown(float NewAxisValue)
{
	FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);

	Direction.Z = 0.0f;
	Direction.Normalize();

	AddMovementInput(Direction, NewAxisValue);
}

void ASurvivorPreviewCharacter::LeftRight(float NewAxisValue)
{
	FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);

	Direction.Z = 0.0f;
	Direction.Normalize();

	AddMovementInput(Direction, NewAxisValue);
}

void ASurvivorPreviewCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void ASurvivorPreviewCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}