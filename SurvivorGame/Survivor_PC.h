// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Survivor_PC.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORGAME_API ASurvivor_PC : public APlayerController
{
	GENERATED_BODY()

		ASurvivor_PC();

public:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PostInitializeComponents() override; // 여기서 빙의되는지 알 수 있음
	virtual void SetupInputComponent() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	void GetDamageHUD();
	void WeaponUIVisible();
	void WeaponUIHidden();
private:
	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Pawn)
		class ASurvivorCharacter* myCharacter;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Run)
		bool bCanRun;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Crouch)
		bool bCanCrouching;

	class UMyGameInstance* myGameInstance;
private:
	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	UFUNCTION(Server, Reliable)
		void Server_GoRightOrLeft(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_GoRightOrLeft(ASurvivorCharacter* ClientCharacter);

	void GoRightOrLeft();

	UFUNCTION(Server, Reliable)
		void Server_StopRightOrLeft(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_StopRightOrLeft(ASurvivorCharacter* ClientCharacter);

	void StopRightOrLeft();

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);

	// 달리기 함수

	UFUNCTION(Server, Reliable)
		void Server_Run(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_Run(ASurvivorCharacter* ClientCharacter);

	void Run();

	UFUNCTION(Server, Reliable)
		void Server_StopRun(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_StopRun(ASurvivorCharacter* ClientCharacter);

	void StopRun();

	void Jump();

	void StopJumping();

	UFUNCTION(Server, Reliable)
		void Server_GetItem(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_GetItem(ASurvivorCharacter* ClientCharacter);

	void GetItem();

	UFUNCTION(Server, Reliable)
		void Server_Crouching(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_Crouching(ASurvivorCharacter* ClientCharacter);

	void Crouching();

	UFUNCTION(Server, Reliable)
		void Server_StopCrouching(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_StopCrouching(ASurvivorCharacter* ClientCharacter);

	void StopCrouching();

	UFUNCTION(Server, Reliable)
		void Server_PlayerAttack(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_PlayerAttack(ASurvivorCharacter* ClientCharacter);

	void PlayerAttack();

	UFUNCTION(Server, Reliable)
		void Server_ToAim(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_ToAim(ASurvivorCharacter* ClientCharacter);

	void ToAim();

	UFUNCTION(Server, Reliable)
		void Server_EndAim(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_EndAim(ASurvivorCharacter* ClientCharacter);

	void EndAim();

	UFUNCTION(Server, Reliable)
		void Server_Reload(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_Reload(ASurvivorCharacter* ClientCharacter);

	void Reload();

	UFUNCTION(Server, Reliable)
		void Server_ReloadEnd(ASurvivorCharacter* ClientCharacter);

	UFUNCTION(Client, Reliable)
		void Client_ReloadEnd(ASurvivorCharacter* ClientCharacter);

	void ReloadEnd();
};
