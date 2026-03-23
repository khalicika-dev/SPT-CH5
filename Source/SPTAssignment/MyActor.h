// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class SPTASSIGNMENT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle handle;
	int moveCnt = 0;
	int rotCnt = 0;
	int eventCnt = 0;
	float TotalDist = 0.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move(float distance);
	void Turn(float angle);
	void TriggerEvent();
};
