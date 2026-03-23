// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	
	GetWorld()->GetTimerManager().SetTimer(handle, [&]()
		{
			Move(FMath::FRand() * 50.0f);
			Turn(FMath::FRand() * 45.0f);
			TriggerEvent();
		}
	, 1.0f,true);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (moveCnt >= 10)
	{
		GetWorld()->GetTimerManager().ClearTimer(handle);
		GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Emerald,
			FString::Printf(TEXT("TotalDist: %f, EventCount: %d"),
				TotalDist,eventCnt));
		moveCnt = -1;
	}
}

void AMyActor::Move(float distance)
{
	FVector vec = FMath::VRand() * distance;
	FVector oldLoc = GetActorLocation();
	FVector newLoc = oldLoc + vec;
	float dist = FVector::Dist(oldLoc, newLoc);
	//UE_LOG(LogTemp, Display, TEXT("%s, %f"), *vec.ToString(), vec.Length());
	
	moveCnt++;
	TotalDist += dist;
	SetActorLocation(newLoc);
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Yellow, 
		FString::Printf(TEXT("[%d Times] %s (+ %s, Disatance: %f)"),
			moveCnt, *newLoc.ToString(), *vec.ToString(), dist));

}

void AMyActor::Turn(float angle)
{
	FRotator rot = FRotator::ZeroRotator;
	FRotator oldRot = GetActorRotation();
	FRotator newRot = oldRot;
	int r = FMath::Rand() % 3;
	switch (r)
	{
	case 0:
		rot.Roll = angle * (FMath::Rand() % 2 == 0 ? 1 : -1);
		break;
	case 1:
		rot.Pitch = angle * (FMath::Rand() % 2 == 0 ? 1 : -1);
		break;
	case 2:
		rot.Yaw = angle * (FMath::Rand() % 2 == 0 ? 1 : -1);
		break;
	}
	newRot += rot;

	rotCnt++;
	SetActorRotation(newRot);
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Cyan,
		FString::Printf(TEXT("[%d Times] %s (+ %s, Angle: %f)"),
			rotCnt, *newRot.ToString(), *rot.ToString(), angle));
}

void AMyActor::TriggerEvent()
{
	if (FMath::Rand() % 2 == 0)
	{
		eventCnt++;
		GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red,
			TEXT("An event occurred!"));
	}
}