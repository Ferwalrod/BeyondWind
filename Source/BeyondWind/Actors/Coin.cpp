// Fill out your copyright notice in the Description page of Project Settings.


#include "BeyondWind/Actors/Coin.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "BeyondWind/Characters/BlockPlayer.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ACoin::ACoin():m_iScoreAmount(100),m_fRotationSpeed(5.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mc_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mc_Root);
	mc_BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collision"));
	mc_BoxCollision->SetupAttachment(mc_Root);
	mc_BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnBeginOverlap);
	mc_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mc_Mesh->SetupAttachment(mc_BoxCollision);
	
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/BeyondWind/Misc/FloatingCurve.FloatingCurve'"));
	if (Curve.Succeeded())
	{
		m_pCurve = Curve.Object;
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the floating curve, something went wrong :("));
	}

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	if (m_pCurve)
	{
		FOnTimelineFloat TimeDelegate;
		TimeDelegate.BindUFunction(this, FName("FloatingFunction"));
		m_Timeline.AddInterpFloat(m_pCurve, TimeDelegate);
		m_Timeline.SetLooping(true);
		m_Timeline.Play();
	}
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_Timeline.TickTimeline(DeltaTime);
	AddActorWorldRotation(FRotator(0.f, m_fRotationSpeed, 0.f));
}

void ACoin::OnBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABlockPlayer* pPlayer = Cast<ABlockPlayer>(OtherActor);
	if (pPlayer)
	{
		pPlayer->m_iScore += m_iScoreAmount;
		this->Destroy();
	}
}

void ACoin::FloatingFunction(float value)
{
	mc_BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, value));
}


