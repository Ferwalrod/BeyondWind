// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeyondWind/Actors/BaseBlock.h"
#include "Floor.generated.h"

class UInstancedStaticMeshComponent;

UCLASS()
class BEYONDWIND_API AFloor : public ABaseBlock
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", DisplayName = "InstancedBlock")
	UInstancedStaticMeshComponent* mc_InstancedBlock;

	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "FloorSizeX")
	int m_iFloorSizeX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "FloorSizeY")
	int m_iFloorSizeY;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnConstruction(const FTransform& Transform);
};
