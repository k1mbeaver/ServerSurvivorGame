// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "EquipDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FEquipDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* EquipHead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* EquipUpper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* EquipUnder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* EquipShoes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* EquipBag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* EquipWeapon;
};

UCLASS()
class SURVIVORGAME_API AEquipDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
