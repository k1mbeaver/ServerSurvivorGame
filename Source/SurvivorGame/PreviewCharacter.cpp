// Fill out your copyright notice in the Description page of Project Settings.


#include "PreviewCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
APreviewCharacter::APreviewCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
}

// Called when the game starts or when spawned
void APreviewCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APreviewCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APreviewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APreviewCharacter::UpDown(float NewAxisValue)
{
	FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);

	Direction.Z = 0.0f;
	Direction.Normalize();

	AddMovementInput(Direction, NewAxisValue);
}

void APreviewCharacter::LeftRight(float NewAxisValue)
{
	FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);

	Direction.Z = 0.0f;
	Direction.Normalize();

	AddMovementInput(Direction, NewAxisValue);
}

void APreviewCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void APreviewCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}