// Fill out your copyright notice in the Description page of Project Settings.


#include "Automatinator/StuckRecordComponent.h"
#include "TimerManager.h"
#include "Misc/CString.h"
#include "HAL/FileManager.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DateTime.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

// Sets default values for this component's properties
UStuckRecordComponent::UStuckRecordComponent():m_fRecordRate(1.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStuckRecordComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &UStuckRecordComponent::Record, m_fRecordRate, true);
}


void UStuckRecordComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	FString FileName = "StuckResult_";
	FDateTime Date = FDateTime::Now();
	FileName.Append(Date.ToString());
	FileName.Append(TEXT(".txt"));
	TArray<FString> Results;
	FString Line;
	for (auto It = m_StuckCountMap.CreateConstIterator(); It; ++It) {
		Line = It.Key().ToString().Append(TEXT("||")).Append(FString::FromInt(It.Value()));
		Results.Add(Line);
	}
	FString Dir = FPaths::ProjectContentDir().Append("/BeyondWind/Files/");
	FString FileDir = Dir.Append(FileName);

	if (FFileHelper::SaveStringArrayToFile(Results, *FileDir))
	{
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Sucsesfuly Written: \"%d\" FStrings to the text file"), Results.Num());

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not save the stuck results, something wrong :("));
	}
}

// Called every frame
void UStuckRecordComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStuckRecordComponent::Record()
{
	UE_LOG(LogTemp, Warning, TEXT("Recording data for stuck"));
	FVector Loc = UKismetMathLibrary::Vector_SnappedToGrid(GetOwner()->GetActorLocation(), 300.f);
	if (m_StuckCountMap.Contains(Loc)) {
		m_StuckCountMap[Loc] += 1;
	}
	else {
		m_StuckCountMap.Add(Loc, 1);
	}
}

