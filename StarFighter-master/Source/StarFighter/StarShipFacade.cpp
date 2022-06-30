// Fill out your copyright notice in the Description page of Project Settings.


#include "StarShipFacade.h"
#include "StarShipNavigationOfficer.h"
#include "StarShipOperationsOfficer.h"
#include "StarShipSupplyOfficer.h"

// Sets default values
AStarShipFacade::AStarShipFacade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStarShipFacade::BeginPlay()
{
	Super::BeginPlay();

	//Initialize the lists
	Crew = TArray<AStarShipCrewMember*>();
	Tasks = TArray<FString>();
	//Spawn the members
	AStarShipNavigationOfficer* NavOfficer = GetWorld()->SpawnActor<AStarShipNavigationOfficer>(AStarShipNavigationOfficer::StaticClass());
	AStarShipOperationsOfficer* OpsOfficer = GetWorld()->SpawnActor<AStarShipOperationsOfficer>(AStarShipOperationsOfficer::StaticClass());
	AStarShipSupplyOfficer* SupOfficer = GetWorld()->SpawnActor<AStarShipSupplyOfficer>(AStarShipSupplyOfficer::StaticClass());
	//Add the member to the crew
	Crew.Add(NavOfficer);
	Crew.Add(OpsOfficer);
	Crew.Add(SupOfficer);
	
}

// Called every frame
void AStarShipFacade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStarShipFacade::Reveille()
{
	//Empty the task list
	Tasks.Empty();
	//Add the tasks to execute
	Tasks.Add("trice_up");
	Tasks.Add("muster");
	//Execute the tasks
	PerformTasks(Crew, Tasks);
}

void AStarShipFacade::PlanOfTheDay()
{
	//Empty the task list
	Tasks.Empty();
	//Add the task to execute
	Tasks.Add("duty");
	//Execute the tasks
	PerformTasks(Crew, Tasks);
}

void AStarShipFacade::Taps()
{
	//Empty the task list
	Tasks.Empty();
	//Add the tasks to execute
	Tasks.Add("liberty_call");
	Tasks.Add("lights_out");
	//Execute the tasks
	PerformTasks(Crew, Tasks);
}

void AStarShipFacade::PerformTasks(TArray<AStarShipCrewMember*>
	myCrew, TArray<FString> myTasks)
{
	//Execute the passed tasks for each crew member
	for (AStarShipCrewMember* Member : myCrew)
	{
		//Execute the task
		Member->Task(myTasks);
	}
}
