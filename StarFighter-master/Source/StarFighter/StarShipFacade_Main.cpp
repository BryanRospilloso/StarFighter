// Fill out your copyright notice in the Description page of Project Settings.


#include "StarShipFacade_Main.h"
#include "StarShipFacade.h"

// Sets default values
AStarShipFacade_Main::AStarShipFacade_Main()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStarShipFacade_Main::BeginPlay()
{
	Super::BeginPlay();

	//Create the Ship Facade Actor
	AStarShipFacade* ShipFacade = GetWorld()->SpawnActor<AStarShipFacade>(AStarShipFacade::StaticClass());
	//Execute the needed tasks
	ShipFacade->Reveille();
	ShipFacade->PlanOfTheDay();
	ShipFacade->Taps();
	
}

// Called every frame
void AStarShipFacade_Main::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

