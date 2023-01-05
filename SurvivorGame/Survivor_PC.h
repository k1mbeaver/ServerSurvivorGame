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

private:
	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Pawn)
		class ASurvivorCharacter* myCharacter;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Run)
		bool bCanRun;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Crouch)
		bool bCanCrouching;

private:
	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

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

	void GetItem();

	void Crouching();

	void StopCrouching();

	void PlayerAttack();

	void ToAim();

	void EndAim();

	void Reload();
};
