// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor_PC.h"
#include "SurvivorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerAnimInstance.h"
#include "PlayerHUD.h"
#include "MyGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

ASurvivor_PC::ASurvivor_PC()
{

}

void ASurvivor_PC::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (aPawn)
	{
		myCharacter = Cast<ASurvivorCharacter>(aPawn);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Success!"));
		SetInputMode(FInputModeGameOnly());

		bCanRun = true;
		bCanCrouching = true;

		myCharacter->CharacterAnim->ReloadEnd_Reload.AddUObject(this, &ASurvivor_PC::ReloadEnd);

		myGameInstance = Cast<UMyGameInstance>(GetGameInstance());
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
	InputComponent->BindAction(TEXT("RightLeft"), IE_Pressed, this, &ASurvivor_PC::GoRightOrLeft);
	InputComponent->BindAction(TEXT("RightLeft"), IE_Released, this, &ASurvivor_PC::StopRightOrLeft);

	//캐릭터 달리기
	InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &ASurvivor_PC::Run);
	InputComponent->BindAction(TEXT("Run"), IE_Released, this, &ASurvivor_PC::StopRun);

	// 캐릭터 점프
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ASurvivor_PC::Jump);
	InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ASurvivor_PC::StopJumping);

	// 캐릭터 앉기
	InputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &ASurvivor_PC::Crouching);
	InputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &ASurvivor_PC::StopCrouching);

	// 캐릭터 아이템 얻기
	InputComponent->BindAction(TEXT("ItemGet"), IE_Pressed, this, &ASurvivor_PC::GetItem);

	// 캐릭터 공격
	InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ASurvivor_PC::PlayerAttack);

	// 캐릭터 장전
	InputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &ASurvivor_PC::Reload);

	// 캐릭터 견착
	InputComponent->BindAction(TEXT("Aim"), IE_Pressed, this, &ASurvivor_PC::ToAim);
	InputComponent->BindAction(TEXT("Aim"), IE_Released, this, &ASurvivor_PC::EndAim);
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

void ASurvivor_PC::GoRightOrLeft()
{
	if (myCharacter)
	{
		myCharacter->GoRightOrLeft();
		Server_GoRightOrLeft(myCharacter);
	}
}

void ASurvivor_PC::Server_GoRightOrLeft_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->GoRightOrLeft();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_GoRightOrLeft(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_GoRightOrLeft_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->GoRightOrLeft();
	//ClientCharacter->GetCharacterMovement()->MaxWalkSpeed = ClientCharacter->fSprintPawnSpeed;
}

void ASurvivor_PC::StopRightOrLeft()
{
	if (myCharacter)
	{
		myCharacter->StopRightOrLeft();
		Server_StopRightOrLeft(myCharacter);
	}
}

void ASurvivor_PC::Server_StopRightOrLeft_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->StopRightOrLeft();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_StopRightOrLeft(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_StopRightOrLeft_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->StopRightOrLeft();
	//ClientCharacter->GetCharacterMovement()->MaxWalkSpeed = ClientCharacter->fSprintPawnSpeed;
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
	if (bCanRun == true)
	{
		if (myCharacter == nullptr) return;

		//myCharacter->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
		myCharacter->Run();
		Server_Run(myCharacter);
	}
}

void ASurvivor_PC::Server_Run_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->Run();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_Run(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_Run_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->Run();
	//ClientCharacter->GetCharacterMovement()->MaxWalkSpeed = ClientCharacter->fSprintPawnSpeed;
}

void ASurvivor_PC::StopRun()
{
	if (bCanRun == true)
	{
		if (myCharacter == nullptr) return;

		//myCharacter->GetCharacterMovement()->MaxWalkSpeed = 200.0f;
		myCharacter->StopRun();
		Server_StopRun(myCharacter);
	}
}

void ASurvivor_PC::Server_StopRun_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->StopRun();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_StopRun(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_StopRun_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->StopRun();
	//ClientCharacter->GetCharacterMovement()->MaxWalkSpeed = ClientCharacter->fCurrentPawnSpeed;
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
		Server_Crouching(myCharacter);
	}
}

void ASurvivor_PC::Server_Crouching_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->Crouching();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_Crouching(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_Crouching_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->Crouching();
}

void ASurvivor_PC::StopCrouching()
{
	if (myCharacter)
	{
		Server_StopCrouching(myCharacter);
	}
}

void ASurvivor_PC::Server_StopCrouching_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->StopCrouching();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_StopCrouching(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_StopCrouching_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->StopCrouching();
}

void ASurvivor_PC::GetItem()
{
	if (myCharacter)
	{
		// 나중에 E 버튼을 눌러서 이 함수가 실행되게 하자(지금은 닿기만 해도 아이템 획득)
		APlayerHUD* HUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

		HUD->SetImage(myGameInstance->GetItemImage("1"));
		HUD->SetImageUse();
		HUD->SetImageVisible();

		//Server_GetItem(myCharacter);
	}
}

void ASurvivor_PC::Server_GetItem_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->GetItem();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_GetItem(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_GetItem_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->GetItem();
}

void ASurvivor_PC::PlayerAttack()
{
	if (myCharacter)
	{
		Server_PlayerAttack(myCharacter);
	}
}

void ASurvivor_PC::Server_PlayerAttack_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->PlayerAttack();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_PlayerAttack(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_PlayerAttack_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->PlayerAttack();
}

void ASurvivor_PC::ToAim()
{
	if (myCharacter)
	{
		Server_ToAim(myCharacter);
	}
}

void ASurvivor_PC::Server_ToAim_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_ToAim(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_ToAim_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->ToAim();
}

void ASurvivor_PC::EndAim()
{
	if (myCharacter)
	{
		Server_EndAim(myCharacter);
	}
}

void ASurvivor_PC::Server_EndAim_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_EndAim(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_EndAim_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->EndAim();
}

void ASurvivor_PC::Reload()
{
	if (myCharacter)
	{
		Server_Reload(myCharacter);
	}
}

void ASurvivor_PC::Server_Reload_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->Reload();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_Reload(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_Reload_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->Reload();
}

void ASurvivor_PC::ReloadEnd()
{
	if (myCharacter)
	{
		Server_ReloadEnd(myCharacter);
	}
}

void ASurvivor_PC::Server_ReloadEnd_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->ReloadEnd();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_ReloadEnd(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_ReloadEnd_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->ReloadEnd();
}

void ASurvivor_PC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASurvivor_PC, bCanRun);
	DOREPLIFETIME(ASurvivor_PC, bCanCrouching); 
	DOREPLIFETIME(ASurvivor_PC, myCharacter);
}