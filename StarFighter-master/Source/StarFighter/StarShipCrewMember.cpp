// Fill out your copyright notice in the Description page of Project Settings.


#include "StarShipCrewMember.h"

// Sets default values
AStarShipCrewMember::AStarShipCrewMember()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStarShipCrewMember::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStarShipCrewMember::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStarShipCrewMember::TurnLightsOut()
{
	// Print lights out string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s taps,taps lights out."), *CrewTitle()));
}
void AStarShipCrewMember::HeaveOutTriceUp()
{
	// Print trice up string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s all hands heave out and trice up."), *CrewTitle()));
}
void AStarShipCrewMember::LibertyCall()
{
	// Print liberty call string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s liberty call, liberty call."), *CrewTitle()));
}
void AStarShipCrewMember::CrewMuster()
{
	// Print crew muster string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s time for muster."), *CrewTitle()));
}
void AStarShipCrewMember::Task(const TArray<FString>& Tasks)
{
	//Loop the Tasks array and call the Task() function for each of them
	for (const FString& myTask : Tasks)
	{
		Task(myTask);
	}
}
void AStarShipCrewMember::Task(const FString& Task)
{
	//Checks which task must be executed
	if (Task.Equals("lights_out"))
	{
		TurnLightsOut();
	}
	else if (Task.Equals("trice_up"))
	{
		HeaveOutTriceUp();
	}
	else if (Task.Equals("liberty_call"))
	{
		LibertyCall();
	}
	else if (Task.Equals("muster"))
	{
		CrewMuster();
	}
	else if (Task.Equals("duty"))
	{
		Duty();
	}
	else
	{
		//In case the passed Task doesn't exist
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("Undefined task"));
	}
}

