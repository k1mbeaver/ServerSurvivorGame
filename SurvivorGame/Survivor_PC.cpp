// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor_PC.h"
#include "SurvivorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ASurvivor_PC::ASurvivor_PC()
{

}

void ASurvivor_PC::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (aPawn)
	{
		myCharacter = Cast<ASurvivorCharacter>(aPawn);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Success!"));
		SetInputMode(FInputModeGameOnly());
	}
}

void ASurvivor_PC::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Possess!"));
}

void ASurvivor_PC::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 캐릭터 이동 함수
	InputComponent->BindAxis(TEXT("MoveForward"), this, &ASurvivor_PC::UpDown);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ASurvivor_PC::LeftRight);
	InputComponent->BindAxis(TEXT("LookUp"), this, &ASurvivor_PC::LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &ASurvivor_PC::Turn);
}

void ASurvivor_PC::UpDown(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->UpDown(NewAxisValue);
	}
}

void ASurvivor_PC::LeftRight(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->LeftRight(NewAxisValue);
	}
}

void ASurvivor_PC::LookUp(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->LookUp(NewAxisValue);
	}
}

void ASurvivor_PC::Turn(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->Turn(NewAxisValue);
	}
}