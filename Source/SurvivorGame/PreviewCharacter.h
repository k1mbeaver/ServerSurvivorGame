// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PreviewCharacter.generated.h"

UCLASS()
class SURVIVORGAME_API APreviewCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APreviewCharacter();

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	void GoRightOrLeft();

	void StopRightOrLeft();

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);
};
