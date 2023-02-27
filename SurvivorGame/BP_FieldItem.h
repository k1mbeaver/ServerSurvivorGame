// Fill out your copyright notice in the Description page of Project Settings.
// #include "ItemDataStruct.h"
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "BP_FieldItem.generated.h"


UCLASS()
class SURVIVORGAME_API ABP_FieldItem : public AActor
{
	GENERATED_BODY()
	
private:
	class UMyGameInstance* MyGameInstance;

	UPROPERTY(EditAnyWhere, Replicated, BlueprintReadOnly, Category = ItemID, Meta = (AllowPrivateAccess = true))
		FString ItemID;

public:
	// Sets default values for this actor's properties
	ABP_FieldItem();

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Item)
		FString ItemName;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Item)
		int nDefaultBullet;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Item)
		bool bIsWeapon = false;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Item)
		class USkeletalMesh* ItemSkeletal;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Item)
		class USkeletalMeshComponent* ItemSkeletalMesh;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		int GetDefaultBullet();

	UFUNCTION(BlueprintCallable)
		FString GetItemID();

	UFUNCTION(BlueprintCallable)
		FString GetItemName();

	UFUNCTION(BlueprintCallable)
		USkeletalMesh* GetSkeletalMesh();

	UFUNCTION(BlueprintCallable)
		bool GetIsWeapon();
};
