// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleShip.h"

// Sets default values
ABattleShip::ABattleShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattleShip::AlterManeuvers(AActor* myBattleStrategy)
{
	BattleStrategy = Cast<IBattleShipStrategy>(myBattleStrategy);
	//Log Error if the cast failed
	if (!BattleStrategy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("Invalid Cast! See Output log for more details"));
		UE_LOG(LogTemp, Error, TEXT("AlterManeuvers(): The Actor is nota BattleShipStrategy!Are you sure that the Actor implements thatinterface ? "));
	}

}

void ABattleShip::Engage()
{
	//Log Error if the current Strategy is NULL
	if (!BattleStrategy) { UE_LOG(LogTemp, Error, TEXT("Engage():BattleStrategy is NULL, make sure it's initialized.")); return; }
	//Execute the current Strategy Maneuver
	BattleStrategy->Maneuver();
}

