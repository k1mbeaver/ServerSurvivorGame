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

/*
void ASurvivor_PC::SetupInputComponent()
{
	Super::SetupInputComponent();

	// ĳ���� �̵� �Լ�
	InputComponent->BindAxis(TEXT("MoveForward"), this, &ASurvivor_PC::UpDown);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ASurvivor_PC::LeftRight);
	InputComponent->BindAxis(TEXT("LookUp"), this, &ASurvivor_PC::LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &ASurvivor_PC::Turn);

	// ĳ���� �޸���
	InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &ASurvivor_PC::Run);
	InputComponent->BindAction(TEXT("Run"), IE_Released, this, &ASurvivor_PC::StopRun);

	// ĳ���� ����
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ASurvivor_PC::Jump);
	InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ASurvivor_PC::StopJumping);

	// ĳ���� �ɱ�
	InputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &ASurvivor_PC::Crouching);
	InputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &ASurvivor_PC::StopCrouching);

	// ĳ���� ������ ���
	InputComponent->BindAction(TEXT("ItemGet"), IE_Pressed, this, &ASurvivor_PC::GetItem);

	// ĳ���� ����
	InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ASurvivor_PC::PlayerAttack);

	// ĳ���� ����
	InputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &ASurvivor_PC::Reload);

	// ĳ���� ����
	InputComponent->BindAction(TEXT("Aim"), IE_Pressed, this, &ASurvivor_PC::ToAim);
	InputComponent->BindAction(TEXT("Aim"), IE_Released, this, &ASurvivor_PC::EndAim);
}
*/
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

void ASurvivor_PC::Run()
{
	if (myCharacter)
	{
		myCharacter->Run();
	}
}

void ASurvivor_PC::StopRun()
{
	if (myCharacter)
	{
		myCharacter->StopRun();
	}
}

void ASurvivor_PC::Jump()
{
	if (myCharacter)
	{
		myCharacter->Jump();
	}
}

void ASurvivor_PC::StopJumping()
{
	if (myCharacter)
	{
		myCharacter->StopJumping();
	}
}

void ASurvivor_PC::Crouching()
{
	if (myCharacter)
	{
		myCharacter->Crouching();
	}
}

void ASurvivor_PC::StopCrouching()
{
	if (myCharacter)
	{
		myCharacter->StopCrouching();
	}
}

void ASurvivor_PC::GetItem()
{
	if (myCharacter)
	{
		myCharacter->GetItem();
	}
}

void ASurvivor_PC::PlayerAttack()
{
	if (myCharacter)
	{
		myCharacter->PlayerAttack();
	}
}

void ASurvivor_PC::ToAim()
{
	if (myCharacter)
	{
		myCharacter->ToAim();
	}
}

void ASurvivor_PC::EndAim()
{
	if (myCharacter)
	{
		myCharacter->EndAim();
	}
}

void ASurvivor_PC::Reload()
{
	if (myCharacter)
	{
		myCharacter->Reload();
	}
}