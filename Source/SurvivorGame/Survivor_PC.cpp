// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor_PC.h"
#include "SurvivorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerAnimInstance.h"
#include "PlayerHUD.h"
#include "MyGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "InventorySystem.h"
#include "PlayerItemData.h"
#include "PreviewCharacter.h"
#include "SurvivorPreviewCharacter.h"
#include "Components/CapsuleComponent.h"

ASurvivor_PC::ASurvivor_PC()
{
	
	static ConstructorHelpers::FClassFinder<ASurvivorPreviewCharacter> PREVIEW_CHARACTER(TEXT("Blueprint'/Game/Blueprints/MySurvivorPreviewCharacter.MySurvivorPreviewCharacter_C'"));
	if (PREVIEW_CHARACTER.Succeeded())
	{
		PreviewClass = PREVIEW_CHARACTER.Class;
	}
	
}

void ASurvivor_PC::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (bGameEnd != true)
	{
		if (aPawn)
		{
			myCharacter = Cast<ASurvivorCharacter>(aPawn);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Success!"));
			SetInputMode(FInputModeGameOnly());

			bCanRun = true;
			bCanCrouching = true;

			myCharacter->CharacterAnim->ReloadEnd_Reload.AddUObject(this, &ASurvivor_PC::ReloadEnd);
			myCharacter->MyPlayerController = this;

			myGameInstance = Cast<UMyGameInstance>(GetGameInstance());

			playerHUD = GetHUD<APlayerHUD>();

			playerCharacterDefaultHP = myCharacter->PlayerDefaultHP;
			playerCharacterDefaultStamina = myCharacter->PlayerDefaultStamina;
		}
	}

	/*
	else
	{
		if (aPawn)
		{
			myPreviewCharacter = Cast<ASurvivorPreviewCharacter>(aPawn);
		}
	}
	*/
}

void ASurvivor_PC::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Possess!"));
}

void ASurvivor_PC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsHealth)
	{
		APlayerHUD* HUD = GetHUD<APlayerHUD>();
		if (HUD == nullptr) return;
		playerCharacterDefaultHP = myCharacter->PlayerDefaultHP;
		HUD->SetHealthPersent(playerCharacterHP / playerCharacterDefaultHP);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("GageChange!"));
		IsHealth = false;
	}

	if (IsRun)
	{
		APlayerHUD* HUD = GetHUD<APlayerHUD>();
		if (HUD == nullptr) return;
		if (myCharacter->PlayerStamina <= 0)
		{
			myCharacter->GetCharacterMovement()->MaxWalkSpeed = myCharacter->fSprintPawnSpeed;
			return;
		}
		myCharacter->PlayerStamina -= 0.05f;
		playerCharacterDefaultStamina = myCharacter->PlayerDefaultStamina;
		playerCharacterStamina = myCharacter->PlayerStamina;
		HUD->SetStaminaPersent(playerCharacterStamina / playerCharacterDefaultStamina);
	}
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

	// 캐릭터 총 장착
	InputComponent->BindAction(TEXT("EquipGun"), IE_Pressed, this, &ASurvivor_PC::EquipGun);

	// 캐릭터 공격
	InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ASurvivor_PC::PlayerAttack);

	// 캐릭터 장전
	InputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &ASurvivor_PC::Reload);

	// 캐릭터 견착
	InputComponent->BindAction(TEXT("Aim"), IE_Pressed, this, &ASurvivor_PC::ToAim);
	InputComponent->BindAction(TEXT("Aim"), IE_Released, this, &ASurvivor_PC::EndAim);

	// 인벤토리 열기
	InputComponent->BindAction(TEXT("Inventory"), IE_Pressed, this, &ASurvivor_PC::UseInventory);

	// 캐릭터 견착
	InputComponent->BindAction(TEXT("Esc"), IE_Pressed, this, &ASurvivor_PC::PressEsc);
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

void ASurvivor_PC::UseInventory()
{
	if (IsUIopen)
	{
		APlayerHUD* HUD = GetHUD<APlayerHUD>();
		if (HUD == nullptr) return;
		FInputModeGameOnly InputMode;
		UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(false);
		HUD->SetInventoryHidden();
		IsUIopen = false;
	}

	else
	{
		APlayerHUD* HUD = GetHUD<APlayerHUD>();
		if (HUD == nullptr) return;

		FInputModeUIOnly InputMode;
		UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
		ASurvivorCharacter* myPlayerCharacter = Cast<ASurvivorCharacter>(GetPawn());
		TArray<UPlayerItemData*> GetInventoryData = myCharacter->GetItemInventory();
		UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

		//if (GetInventoryData.Num() == 0)
		//{
			//return;
		//} 

		//GetInventoryData.Num()

		HUD->ListUpdate();
		if (myPlayerCharacter->bHasGun == true)
		{
			HUD->SetWeaponImage(MyGI->GetItemImage(myPlayerCharacter->GunItemID));
		}

		for (int Index = 1; Index <= 2; Index++)
		{
			//UPlayerItemData* GetItemData = GetInventoryData[Index];
			//FString strName = GetItemData->GetItemName();
			//int nCount = GetItemData->GetItemCount();
			//UTexture2D* setImage = GetItemData->GetItemImage();
			
			FString strIndex = FString::FromInt(Index);
			FString strName = MyGI->GetInventoryItemName(Index);
			int nCount = MyGI->GetInventoryCount(Index);
			UTexture2D* setImage = MyGI->GetInventoryImage(Index);
			HUD->SetListView(Index - 1, strName, nCount, setImage);
		}

		HUD->SetInventoryVisible();
		IsUIopen = true;
	}
}

void ASurvivor_PC::UpdateInventory()
{
	APlayerHUD* HUD = GetHUD<APlayerHUD>();
	if (HUD == nullptr) return;

	FInputModeUIOnly InputMode;
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
	ASurvivorCharacter* myPlayerCharacter = Cast<ASurvivorCharacter>(GetPawn());
	TArray<UPlayerItemData*> GetInventoryData = myCharacter->GetItemInventory();
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

	//if (GetInventoryData.Num() == 0)
	//{
		//return;
	//} 

	//GetInventoryData.Num()

	HUD->ListUpdate();

	for (int Index = 1; Index <= 2; Index++)
	{
		//UPlayerItemData* GetItemData = GetInventoryData[Index];
		//FString strName = GetItemData->GetItemName();
		//int nCount = GetItemData->GetItemCount();
		//UTexture2D* setImage = GetItemData->GetItemImage();

		FString strIndex = FString::FromInt(Index);
		FString strName = MyGI->GetInventoryItemName(Index);
		int nCount = MyGI->GetInventoryCount(Index);
		UTexture2D* setImage = MyGI->GetInventoryImage(Index);
		HUD->SetListView(Index - 1, strName, nCount, setImage);
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
		IsRun = true;
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
		IsRun = false;
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
		Server_GetItem(myCharacter);
		//myCharacter->CharacterInventory
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
		if (myCharacter->CurrentWeaponState == EWeaponState::SHOOT)
		{
			if (myCharacter->nProjectileMagazine < 1)
			{
				return;
			}

			// 탄알의 갯수를 줄인다.
			myCharacter->nProjectileMagazine -= 1;

			APlayerHUD* HUD = GetHUD<APlayerHUD>();
			//Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
			if (HUD == nullptr) return;

			HUD->SetProjectileText(myCharacter->nProjectileMagazine);
			HUD->SetDefaultText(myCharacter->nCurrentMagazine);
		}
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
		if (myCharacter->nCurrentMagazine <= 0) // 현재 소유중인 해당 총알의 갯수가 0보다 작으면
		{
			return;
		}

		if (myCharacter->nProjectileMagazine == myCharacter->nDefaultMagazine)
		{
			return;
		}

		if (myCharacter->nCurrentMagazine < myCharacter->nDefaultMagazine) // 
		{
			myCharacter->nProjectileMagazine = myCharacter->nCurrentMagazine;

			myCharacter->nCurrentMagazine = 0;
			return;
		}

		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ReloadEnd!!"));


		int DeleteMagazine = myCharacter->nDefaultMagazine - myCharacter->nProjectileMagazine;
		myCharacter->nCurrentMagazine = myCharacter->nCurrentMagazine - DeleteMagazine;

		myCharacter->nProjectileMagazine = myCharacter->nDefaultMagazine; // nDefaultMagazine 나중에 UI 작업할 때 같이 편집

		APlayerHUD* HUD = GetHUD<APlayerHUD>();
		//Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		if (HUD == nullptr) return;

		UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

		HUD->SetProjectileText(myCharacter->nProjectileMagazine);
		HUD->SetDefaultText(myCharacter->nCurrentMagazine);

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

void ASurvivor_PC::EquipGun()
{
	if (myCharacter)
	{
		if (myCharacter->CurrentWeaponState == EWeaponState::PUNCH)
		{
			// 나중에 E 버튼을 눌러서 이 함수가 실행되게 하자(지금은 닿기만 해도 아이템 획득)
			APlayerHUD* HUD = GetHUD<APlayerHUD>();
			//Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
			if (HUD == nullptr) return;

			UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

			HUD->SetProjectileText(myCharacter->nProjectileMagazine);
			HUD->SetDefaultText(myCharacter->nCurrentMagazine);
			HUD->SetTextVisible();
			HUD->SetImageVisible();
			HUD->SetImage(MyGI->GetItemImage(myCharacter->GunItemID));
			//HUD->SetImage(MyGI->GetItemImage("1"));
			HUD->SetImageUse();

			Server_EquipGun(myCharacter);
		}

		else if (myCharacter->CurrentWeaponState == EWeaponState::SHOOT)
		{
			// 나중에 E 버튼을 눌러서 이 함수가 실행되게 하자(지금은 닿기만 해도 아이템 획득)
			APlayerHUD* HUD = GetHUD<APlayerHUD>();
			//Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
			if (HUD == nullptr) return;

			UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

			HUD->SetTextHidden();
			HUD->SetImageHidden();
			HUD->SetImageNotUse();

			Server_EquipGun(myCharacter);
		}
	}
}

void ASurvivor_PC::Server_EquipGun_Implementation(ASurvivorCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->EquipGun();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_EquipGun(ClientCharacter);
		}
	}
}

void ASurvivor_PC::Client_EquipGun_Implementation(ASurvivorCharacter* ClientCharacter)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->EquipGun();
}

void ASurvivor_PC::GetDamageHUD()
{
	if (myCharacter)
	{
		//APlayerHUD* HUD = GetHUD<APlayerHUD>();
		//Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		//if (HUD == nullptr) return;
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("GETDAMAGE(HUD)!!"));
		Server_GetDamage(myCharacter, myCharacter->GetHP());
		playerCharacterHP = myCharacter->GetHP();
		IsHealth = true;
		//HUD->SetHealthPersent(myCharacter->GetHP() / myCharacter->PlayerDefaultHP);
	}
}

void ASurvivor_PC::GetHealthHUD(float CharacterInfo)
{
	if (myCharacter)
	{
		//APlayerHUD* HUD = GetHUD<APlayerHUD>();
		//Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		//if (HUD == nullptr) return;

		//myCharacter->PlayerHP += 20.0f;
		//myCharacter->GetHP()
		playerCharacterHP = myCharacter->HealthHP(CharacterInfo);
		Server_GetHealth(myCharacter, myCharacter->GetHP());
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("GETHEALTH(HUD)!!"));

		IsHealth = true;
		//float SetCharacterHealth = CharacterInfo;
		//HUD->SetHealthPersent(SetCharacterHealth / myCharacter->PlayerDefaultHP);
		//HUD->SetStaminaPersent(myCharacter->PlayerStamina / myCharacter->PlayerDefaultStamina);
	}
}

void ASurvivor_PC::CharacterHealth(float HealthPercent)
{
	if (myCharacter)
	{
		playerCharacterHP = myCharacter->HealthHP(HealthPercent);
		Server_GetHealth(myCharacter, myCharacter->GetHP());
		IsHealth = true;
	}
}

void ASurvivor_PC::Server_GetDamage_Implementation(ASurvivorCharacter* ClientCharacter, float CharacterHP)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->SetHP(CharacterHP);

	
	//for (AActor* OutActor : OutActors)
	//{
		//ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		//if (PC)
		//{
			//PC->Client_GetDamage(ClientCharacter, CharacterHP);
		//}
	//}
	
}

/*
void ASurvivor_PC::Client_GetDamage_Implementation(ASurvivorCharacter* ClientCharacter, float CharacterHP)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->SetHP(CharacterHP);
}
*/
void ASurvivor_PC::Server_GetHealth_Implementation(ASurvivorCharacter* ClientCharacter, float CharacterHP)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	//TArray<AActor*> OutActors;
	//UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	ClientCharacter->SetHP(CharacterHP);

	
	//for (AActor* OutActor : OutActors)
	//{
		//ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		//if (PC)
		//{
			//PC->Client_GetHealth(ClientCharacter, CharacterHP);
		//}
	//}
	
}


void ASurvivor_PC::Client_GetHealth_Implementation(ASurvivorCharacter* ClientCharacter, float CharacterHP)
{
	if (ClientCharacter == nullptr) return;

	ClientCharacter->SetHP(CharacterHP);
}


void ASurvivor_PC::WeaponUIVisible()
{
	if (myCharacter)
	{
		APlayerHUD* HUD = GetHUD<APlayerHUD>();
		if (HUD == nullptr) return;
		HUD->SetImageUse();
	}
}

void ASurvivor_PC::WeaponUIHidden()
{
	if (myCharacter)
	{
		APlayerHUD* HUD = GetHUD<APlayerHUD>();
		if (HUD == nullptr) return;
		HUD->SetImageNotUse();
	}
}

void ASurvivor_PC::GameDead()
{
	if (myCharacter->CurrentPlayerState == EPlayerState::DEAD)
	{
		APlayerHUD* HUD = GetHUD<APlayerHUD>();
		HUD->SetPreviewUI();

		//bGameEnd = true;
		CurrentDeadPlayer++;
		myCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		myCharacter->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
		myCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		myCharacter->GetCharacterMovement()->MaxWalkSpeed = 800.0f;
		Server_GameDead(CurrentDeadPlayer, myCharacter);
	}
}


void ASurvivor_PC::DestroyCharacter()
{
	//if (myCharacter->CurrentPlayerState == EPlayerState::DEAD)
	//{
		
	//}
	myCharacter->GetMesh()->DestroyComponent();
	FInputModeGameOnly InputMode;
	bGameEnd = true;
	Server_DestroyCharacter(myCharacter);

	/*
	FVector CurrentLocation = myCharacter->GetActorLocation();
	FRotator CurrentRotator = myCharacter->GetActorRotation();

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	bGameEnd = true;
	ASurvivorPreviewCharacter* myPreview = GetWorld()->SpawnActor<ASurvivorPreviewCharacter>(PreviewClass, CurrentLocation, CurrentRotator, ActorSpawnParams);
	myPreviewCharacter = myPreview;
	FInputModeGameOnly InputMode;
	Possess(myPreview);
	*/
}

void ASurvivor_PC::Server_DestroyCharacter_Implementation(ASurvivorCharacter* DestroyCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	DestroyCharacter->GetMesh()->DestroyComponent();

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_DestroyCharacter(DestroyCharacter);
		}
	}
}

void ASurvivor_PC::Client_DestroyCharacter_Implementation(ASurvivorCharacter* DestroyCharacter)
{
	DestroyCharacter->GetMesh()->DestroyComponent();
}

void ASurvivor_PC::Server_GameDead_Implementation(int fCurrentDeadPlayer, ASurvivorCharacter* DestroyCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	int CurrentGamePlayers = OutActors.Num();

	DestroyCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DestroyCharacter->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	DestroyCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	DestroyCharacter->GetCharacterMovement()->MaxWalkSpeed = 800.0f;

	for (AActor* OutActor : OutActors)
	{
		ASurvivor_PC* PC = Cast<ASurvivor_PC>(OutActor);
		if (PC)
		{
			PC->Client_GameDead(CurrentGamePlayers, fCurrentDeadPlayer, DestroyCharacter);
		}
	}
}

void ASurvivor_PC::Client_GameDead_Implementation(int fCurrentMultiPlayer, int fCurrentDeadPlayer, ASurvivorCharacter* DestroyCharacter)
{
	CurrentDeadPlayer = fCurrentDeadPlayer;

	DestroyCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DestroyCharacter->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	DestroyCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	DestroyCharacter->GetCharacterMovement()->MaxWalkSpeed = 800.0f;

	if (myCharacter->CurrentPlayerState == EPlayerState::DEAD)
	{
		if (!bGameEnd)
		{
			FInputModeUIOnly InputMode;
			UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
			APlayerHUD* HUD = GetHUD<APlayerHUD>();
			HUD->SetLose();
			HUD->SetEndVisible();
		}
		//bGameEnd = true;
	}

	else if (myCharacter->CurrentPlayerState == EPlayerState::ALIVE)
	{
		if (CurrentDeadPlayer == fCurrentMultiPlayer - 1)
		{
			FInputModeUIOnly InputMode;
			UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
			APlayerHUD* HUD = GetHUD<APlayerHUD>();
			HUD->SetWin();
			HUD->SetEndVisible();
		}
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("GameEnd!!"));
	}
}

void ASurvivor_PC::PressEsc()
{
	if (!IsEsc)
	{
		IsEsc = true;
		APlayerHUD* HUD = GetHUD<APlayerHUD>();
		HUD->SetEsc(IsEsc);
	}

	else
	{
		IsEsc = false;
		APlayerHUD* HUD = GetHUD<APlayerHUD>();
		HUD->SetEsc(IsEsc);
	}
}

void ASurvivor_PC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASurvivor_PC, bCanRun);
	DOREPLIFETIME(ASurvivor_PC, bCanCrouching);
	DOREPLIFETIME(ASurvivor_PC, myCharacter);
}