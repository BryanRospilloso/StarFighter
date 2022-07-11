// Fill out your copyright notice in the Description page of Project Settings.


#include "BruteForceStrategy.h"

// Sets default values
ABruteForceStrategy::ABruteForceStrategy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABruteForceStrategy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABruteForceStrategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABruteForceStrategy::Maneuver()
{
	//Execute the routine of this type of Strategy
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("We can take these ships head on"));

}

