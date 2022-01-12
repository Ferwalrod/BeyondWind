// Fill out your copyright notice in the Description page of Project Settings.


#include "BeyondWind/Actors/BaseBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABaseBlock::ABaseBlock():m_bIsBreakable(true)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mc_RootScene = CreateDefaultSubobject<USceneComponent>("RootScene");
	SetRootComponent(mc_RootScene);
	mc_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("BlockMesh");
	mc_Mesh->SetupAttachment(RootComponent);
	mc_Mesh->SetRelativeLocation(FVector(50.f, 50.f, 50.f));
	mc_Box = CreateDefaultSubobject<UBoxComponent>("Box");
	mc_Box->SetupAttachment(RootComponent);
	mc_Box->SetRelativeLocation(FVector(50.f, 50.f, 50.f));
	mc_Box->SetBoxExtent(FVector(50.f, 50.f, 50.f), true);
	
}

// Called when the game starts or when spawned
void ABaseBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBlock::GetAttachedLocation(FVector& _ClickLocation , FVector& _Normal , FVector& AttachLocation_)
{
	AttachLocation_ = UKismetMathLibrary::Vector_SnappedToGrid((_ClickLocation + _Normal) - 50.f, 100.f);
}