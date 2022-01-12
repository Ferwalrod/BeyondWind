// Fill out your copyright notice in the Description page of Project Settings.


#include "BeyondWind/Characters/BlockPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"

// Sets default values
ABlockPlayer::ABlockPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mc_SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	mc_SpringArm->SetupAttachment(GetRootComponent());
	mc_Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	mc_Camera->SetupAttachment(mc_SpringArm);

}

// Called when the game starts or when spawned
void ABlockPlayer::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void ABlockPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABlockPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABlockPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABlockPlayer::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ABlockPlayer::MoveUp);
	PlayerInputComponent->BindAxis("LookUp", this, &ABlockPlayer::LookUp);
	PlayerInputComponent->BindAxis("TurnRight", this, &ABlockPlayer::TurnRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABlockPlayer::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABlockPlayer::StopJump);
	PlayerInputComponent->BindAction("NextBlock", IE_Pressed, this, &ABlockPlayer::NextBlock);
	PlayerInputComponent->BindAction("PrevBlock", IE_Pressed, this, &ABlockPlayer::PrevBlock);

}

void ABlockPlayer::GetCrossAirLocation(FVector& _CrossAirLoc)
{

}

bool ABlockPlayer::GetClickOnBlock(const FVector& _Target, FVector& Location_, FVector& Normal_, ABaseBlock* HitBlock_)
{
	return false;
}

void ABlockPlayer::NextBlock()
{
	m_iCurrentBlockIndex = UKismetMathLibrary::Clamp(m_iCurrentBlockIndex++, 0, m_TAllBlocks.Num());
}

void ABlockPlayer::PrevBlock()
{
	m_iCurrentBlockIndex = UKismetMathLibrary::Clamp(m_iCurrentBlockIndex--, 0, m_TAllBlocks.Num());
}

void ABlockPlayer::MoveForward(float value)
{
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.f,GetControlRotation().Yaw,0.f)), value);
}

void ABlockPlayer::MoveRight(float value)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.f, GetControlRotation().Yaw, 0.f)), value);
}

void ABlockPlayer::TurnRight(float value)
{
	AddControllerYawInput(value);
}

void ABlockPlayer::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void ABlockPlayer::MoveUp(float value)
{

}

void ABlockPlayer::StartJump()
{
	Jump();
}

void ABlockPlayer::StopJump()
{
	StopJumping();
}

void ABlockPlayer::PlaceBlock()
{

}

void ABlockPlayer::RemoveBlock()
{

}

