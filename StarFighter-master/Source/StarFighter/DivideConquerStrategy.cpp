// Fill out your copyright notice in the Description page of Project Settings.


#include "DivideConquerStrategy.h"

// Sets default values
ADivideConquerStrategy::ADivideConquerStrategy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADivideConquerStrategy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADivideConquerStrategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADivideConquerStrategy::Maneuver()
{
	//Execute the routine of this type of Strategy
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Lure ships away from each other and attack each individually"));
}
