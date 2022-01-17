// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StuckRecordComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUTOMATINATOR_API UStuckRecordComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	FTimerHandle m_Timer;
public:	
	// Sets default values for this component's properties
	UStuckRecordComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes", DisplayName = "FPS Map")
		TMap<FVector, int> m_StuckCountMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", DisplayName = "Record Rate")
		float m_fRecordRate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Record();
		
};
