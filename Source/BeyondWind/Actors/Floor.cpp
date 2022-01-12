// Fill out your copyright notice in the Description page of Project Settings.


#include "BeyondWind/Actors/Floor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mc_InstancedBlock = CreateDefaultSubobject<UInstancedStaticMeshComponent>("InstancedBlock");
	mc_InstancedBlock->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloor::OnConstruction(const FTransform& Transform) 
{
	Super::OnConstruction(Transform);
	
	SetActorLocation(UKismetMathLibrary::Vector_SnappedToGrid(GetActorLocation(), 100.f), nullptr, false, ETeleportType::None);
	mc_InstancedBlock->ClearInstances();
	for (int x = 0; x < m_iFloorSizeX; x++) {
		for (int y = 0; y < m_iFloorSizeY; y++) {
			mc_InstancedBlock->AddInstance(FTransform(FRotator(0.f, 0.f, 0.f), FVector((x * 100.f) + 50.f, (y * 100.f) + 50.f, 50.f), FVector(1.f, 1.f, 1.f)));
		}
	}
	mc_Box->SetBoxExtent(FVector(m_iFloorSizeX * 50.f, m_iFloorSizeY * 50.f, 50.f), true);
	mc_Box->SetWorldLocation(GetActorLocation() + FVector(m_iFloorSizeX * 50.f, m_iFloorSizeY * 50.f, 50.f), nullptr, false, ETeleportType::None);
}
