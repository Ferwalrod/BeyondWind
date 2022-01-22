// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Coin.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class UBoxComponent;
class UCurveFloat;

UCLASS()
class BEYONDWIND_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();


	//Attributes
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attributes",DisplayName="Score Amount")
	int m_iScoreAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "Rotation Speed")
	float m_fRotationSpeed;
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", DisplayName = "Root")
	USceneComponent* mc_Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", DisplayName = "Mesh")
	UStaticMeshComponent* mc_Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", DisplayName = "Box Collision")
	UBoxComponent* mc_BoxCollision;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	FTimeline m_Timeline;
	UCurveFloat* m_pCurve;
	UFUNCTION()
	void FloatingFunction(float value);
};
