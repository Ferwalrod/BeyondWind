// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrossAirHud.generated.h"

class UTexture2D;

UCLASS()
class BEYONDWIND_API ACrossAirHud : public AHUD
{
	GENERATED_BODY()
private:
	UTexture2D* m_pCross;
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Dimensions",DisplayName="Cross Air X")
		float m_fCrossAirX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dimensions", DisplayName = "Cross Air Y")
		float m_fCrossAirY;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dimensions", DisplayName = "Cross Air Y Location")
		float m_fCrossAirYLocation;


	ACrossAirHud();

	virtual void DrawHUD() override;


	
};
