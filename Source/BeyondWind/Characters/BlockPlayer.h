// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlockPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APlayerController;
class ABaseBlock;

UCLASS()
class BEYONDWIND_API ABlockPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlockPlayer();

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", DisplayName = "SpringArm")
	USpringArmComponent* mc_SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", DisplayName = "Camera")
	UCameraComponent* mc_Camera;

	//Attributes
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "Last Index")
	int m_iLastIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "Current Block Index")
	int m_iCurrentBlockIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "All Blocks")
	TArray<TSubclassOf<ABaseBlock>> m_TAllBlocks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "Fly Tap Delay")
	float m_fFlyTapDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "Fly Tap Delay")
	int m_iFlyTapCounter;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "Target Rotation")
	FRotator m_RTargetRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "Current Rotation")
	FRotator m_RCurrentRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "Furthest Distance to click")
	float m_fFurthestDistanceToClick;

	APlayerController* PlayerControllerRef;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetCrossAirLocation(FVector& _CrossAirLoc);
	bool GetClickOnBlock(const FVector& _Target, FVector& Location_, FVector& Normal_, ABaseBlock* HitBlock_);
	
	//Functions for Action and Axis Inputs

	void NextBlock();
	void PrevBlock();
	void MoveForward(float value);
	void MoveRight(float value);
	void TurnRight(float value);
	void LookUp(float value);
	void MoveUp(float value);
	void StartJump();
	void StopJump();
	void PlaceBlock();
	void RemoveBlock();
};
