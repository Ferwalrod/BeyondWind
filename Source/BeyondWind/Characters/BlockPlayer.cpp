// Fill out your copyright notice in the Description page of Project Settings.


#include "BeyondWind/Characters/BlockPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "BeyondWind/Actors/BaseBlock.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "TimerManager.h"
#include "Animation/AnimMontage.h"
#include "UObject/ConstructorHelpers.h"
#include "BeyondWind/CrossAirHud.h"


// Sets default values
ABlockPlayer::ABlockPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mc_SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	mc_SpringArm->SetupAttachment(GetRootComponent());
	mc_Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	mc_Camera->SetupAttachment(mc_SpringArm);
	//Editor crash because this commented line below
	//GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &ABlockPlayer::OnBlendOut);
	//GetMesh()->GetAnimInstance()->Montage_SetBlendingOutDelegate(FOnMontageBlendingOutStartedMCDelegate::CreateRaw(this, &ABlockPlayer::OnMontageBlendOut));
	//TOFIX: Try to fix the blend.
	static ConstructorHelpers::FObjectFinder<UCurveFloat> FindCurve(TEXT("CurveFloat'/Game/BeyondWind/Misc/RotatingCurve.RotatingCurve'"));
	if (FindCurve.Succeeded()) {
		m_RotatingCurve = FindCurve.Object;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("could not find curve asset"));
	}
	static ConstructorHelpers::FObjectFinder<USoundWave> Sound(TEXT("SoundWave'/Game/BlockGame/Sounds/placeblock.placeblock'"));
	if (Sound.Succeeded()) {
		m_pSound = Sound.Object;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("could not find sound asset"));
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/BlockGame/PlayerCharacter/Animations/BlockCharacterInteractQuickMontage.BlockCharacterInteractQuickMontage'"));
	if (Montage.Succeeded()) {
		m_pAnimMontage = Montage.Object;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("could not find AnimMontage asset"));
	}
	static ConstructorHelpers::FObjectFinder<USoundWave> RemoveSound(TEXT("SoundWave'/Game/BlockGame/Sounds/placeblock.placeblock'"));
	if (RemoveSound.Succeeded()) {
		m_pRemoveBlockSound = RemoveSound.Object;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("could not find remove sound asset"));
	}
}
void ABlockPlayer::OnBlendOut(UAnimMontage* AnimM, bool bInterrupted)
{
	ABaseBlock* Block=GetWorld()->SpawnActor<ABaseBlock>(m_TAllBlocks[m_iCurrentBlockIndex], m_VCurrentAttachLoc,FRotator(0.f,0.f,0.f));
	if (Block) {
		if (m_pSound) {
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_pSound, m_VCurrentAttachLoc);
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Sound pointer is nullptr"));

		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not spawn block, something wrong with block array, cannot find block"));
	}
}

void ABlockPlayer::RotatingFunction(float alpha)
{
	SetActorRotation(UKismetMathLibrary::RLerp(m_RCurrentRotation,m_RTargetRotation,alpha,false));
}

// Called when the game starts or when spawned
void ABlockPlayer::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = GetWorld()->GetFirstPlayerController();
	m_pCrossAir = Cast<ACrossAirHud>(PlayerControllerRef->GetHUD());
	FOnTimelineFloat FloatLine;
	FloatLine.BindUFunction(this, FName("RotatingFunction"));
	m_TimeLine.AddInterpFloat(m_RotatingCurve, FloatLine);
}

// Called every frame
void ABlockPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_TimeLine.TickTimeline(DeltaTime);
}


void ABlockPlayer::StartPlacingBlocks()
{
	GetWorldTimerManager().SetTimer(m_PlaceTimer, this, &ABlockPlayer::PlaceBlock,0.2f,true);
	PlaceBlock();
}


void ABlockPlayer::StopPlacingBlocks()
{
	GetWorldTimerManager().ClearTimer(m_PlaceTimer);
}

void ABlockPlayer::StartRemovingBlocks()
{
	GetWorldTimerManager().SetTimer(m_RemoveTimer, this, &ABlockPlayer::RemoveBlock, 0.2f, true);
	RemoveBlock();
}

void ABlockPlayer::StopRemovingBlocks()
{
	GetWorldTimerManager().ClearTimer(m_RemoveTimer);
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
	PlayerInputComponent->BindAction("PlaceBlock", IE_Pressed, this, &ABlockPlayer::StartPlacingBlocks);
	PlayerInputComponent->BindAction("PlaceBlock", IE_Released, this, &ABlockPlayer::StopPlacingBlocks);
	PlayerInputComponent->BindAction("RemoveBlock", IE_Pressed, this, &ABlockPlayer::StartRemovingBlocks);
	PlayerInputComponent->BindAction("RemoveBlock", IE_Released, this, &ABlockPlayer::StopRemovingBlocks);

}

void ABlockPlayer::GetCrossAirLocation(FVector& CrossAirLoc_)
{
	if (m_pCrossAir) {
		FVector vWorldLoc;
		FVector vWorldDir;
		FVector2D ScreenPos = FVector2D(m_pCrossAir->m_fCrossAirX, m_pCrossAir->m_fCrossAirY);
		UGameplayStatics::DeprojectScreenToWorld(PlayerControllerRef, ScreenPos, vWorldLoc,vWorldDir);
		CrossAirLoc_ = vWorldLoc + (vWorldDir * (m_fFurthestDistanceToClick + mc_SpringArm->TargetArmLength));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not calculate cross air location, did not get Hud reference"));
		CrossAirLoc_ = FVector(0.f, 0.f, 0.f);
	}
}

bool ABlockPlayer::GetClickOnBlock(const FVector& _Target, FVector& Location_, FVector& Normal_, ABaseBlock* HitBlock_)
{
	FHitResult Hit;
	TArray<AActor*> arr;
	bool HasHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), mc_Camera->GetComponentLocation(), _Target, ETraceTypeQuery::TraceTypeQuery1, false, arr, EDrawDebugTrace::None, Hit, true);
	if (HasHit) {
		HitBlock_ = Cast<ABaseBlock>(Hit.Actor);
		if (HitBlock_) {
			Location_ = Hit.Location;
			Normal_ = Hit.Normal;
			return true;
		}
		else {
			Location_ = FVector(0.f, 0.f, 0.f);
			Normal_ = FVector(0.f, 0.f, 0.f);
			HitBlock_ = nullptr;
			return false;
		}
	}
	else {
		Location_ = FVector(0.f, 0.f, 0.f);
		Normal_ = FVector(0.f, 0.f, 0.f);
		HitBlock_ = nullptr;
		return false;
	}
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
	m_RCurrentRotation = GetActorRotation();
	FVector CrossAirLoc;
	GetCrossAirLocation(CrossAirLoc);
	m_RTargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CrossAirLoc);
	m_TimeLine.PlayFromStart();
	FVector Loc, Norm;
	ABaseBlock* AHitBlock=nullptr;
	if (GetClickOnBlock(CrossAirLoc, Loc, Norm, AHitBlock))
	{
		AHitBlock->GetAttachedLocation(Loc, Norm, m_VCurrentAttachLoc);
		if (m_pAnimMontage) {
			GetMesh()->GetAnimInstance()->Montage_Play(m_pAnimMontage, 3.f);
			OnBlendOut(m_pAnimMontage, false);
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Anim montage pointer is null"));
		}
	}
}

void ABlockPlayer::RemoveBlock()
{
	FVector CrossLoc;
	GetCrossAirLocation(CrossLoc);
	FVector Loc, Norm;
	ABaseBlock* AHitBlock = nullptr;
	if (GetClickOnBlock(CrossLoc, Loc, Norm, AHitBlock)) {
		if (AHitBlock) {
			if (AHitBlock->m_bIsBreakable) {
				AHitBlock->Destroy();
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_pRemoveBlockSound, Loc);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("This block is not breakable"));
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Block was not found"));
		}
	}
}

