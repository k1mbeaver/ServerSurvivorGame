// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

private:
	UPROPERTY()
		class ASurvivorCharacter* myCharacter;

private:
	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);

	void Run();

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
