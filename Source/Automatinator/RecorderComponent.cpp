// Fill out your copyright notice in the Description page of Project Settings.


#include "Automatinator/RecorderComponent.h"
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
URecorderComponent::URecorderComponent():m_fRecordRate(0.5f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URecorderComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(m_Timer,this,&URecorderComponent::Record,m_fRecordRate,true);
	
}


void URecorderComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	FString FileName = "Heat_";
	FDateTime Date = FDateTime::Now();
	FileName.Append(Date.ToString(TEXT("yyyy_mm_dd_hh_mm_ss")));
	FileName.Append(TEXT(".txt"));
	TArray<FString> Results;
	FString Line;
	for (auto It = m_FPSMap.CreateConstIterator(); It; ++It) {
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
		UE_LOG(LogTemp, Warning, TEXT("Could not save the results, something wrong :("));
	}

}

// Called every frame
void URecorderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URecorderComponent::Record()
{
	UE_LOG(LogTemp, Warning, TEXT("Recording data"));
	FVector Loc=UKismetMathLibrary::Vector_SnappedToGrid(GetOwner()->GetActorLocation(),100.f);
	int frames=UKismetMathLibrary::Round(1.f/GetWorld()->GetDeltaSeconds());
	m_FPSMap.Add(Loc,frames);
}

