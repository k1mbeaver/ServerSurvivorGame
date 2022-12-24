// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SurvivorGameHUD.generated.h"

UCLASS()
class ASurvivorGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASurvivorGameHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

