// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBlock.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;

UCLASS()
class BEYONDWIND_API ABaseBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBlock();

	//Components
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components",DisplayName="Box")
	UBoxComponent* mc_Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", DisplayName = "BlockMesh")
	UStaticMeshComponent* mc_Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", DisplayName = "RootScene")
	USceneComponent* mc_RootScene;

	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "IsBreakable")
	bool m_bIsBreakable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GetAttachedLocation( FVector& _ClickLocation,
		 FVector& _Normal ,
		FVector& AttachLocation_ );

};
