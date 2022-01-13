// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossAirHud.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"

ACrossAirHud::ACrossAirHud():m_fCrossAirX(0.f),m_fCrossAirY(0.f),m_fCrossAirYLocation(0.25f)
{
	ConstructorHelpers::FObjectFinder<UTexture2D> CrossAir(TEXT("Texture2D'/Game/BlockGame/Materials/Textures/crosshair.crosshair'"));
	if (CrossAir.Succeeded()) {
		m_pCross = CrossAir.Object;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not find cross texture"));
	}
}

void ACrossAirHud::DrawHUD()
{
	Super::DrawHUD();
	m_fCrossAirX = Canvas->SizeX * 0.5f;
	m_fCrossAirY = Canvas->SizeY * m_fCrossAirYLocation;
	if (m_pCross) {
		DrawTexture(m_pCross, m_fCrossAirX - 18.f, m_fCrossAirY - 18.f, 36.f, 36.f, 0.f, 0.f, 1.f, 1.f);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Cross air texture pointer is null"));
	}
	
}
