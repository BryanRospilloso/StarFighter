// Fill out your copyright notice in the Description page of Project Settings.


#include "FreakyAllen.h"
#include "Publisher.h"
#include "ClockTower.h"
#include "NaveTerrestreEnemiga01.h"

// Sets default values
AFreakyAllen::AFreakyAllen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFreakyAllen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFreakyAllen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFreakyAllen::Destroyed()
{
	Super::Destroyed();
	//Log Error if its Clock Tower is NULL
	if (!ClockTower) { UE_LOG(LogTemp, Error, TEXT("Destroyed():ClockTower is NULL, make sure it's initialized.")); return; }
	//Unsubscribe from the Clock Tower if it's destroyed
	ClockTower->UnSubscribe(this);
}

void AFreakyAllen::Update(APublisher* Publisher)
{
	//Execute the routine
	Morph();
}

void AFreakyAllen::Morph()
{
	//Log Error if its Clock Tower is NULL
	if (!ClockTower) { UE_LOG(LogTemp, Error, TEXT("Morph():ClockTower is NULL, make sure it's initialized.")); return; }

	//Get the current time of the Clock Tower
	FString Time = ClockTower->GetTime();

	if (!Time.Compare("Morning"))
	{
		//Execute the Morning routine
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("It is %s, so FreakyAllen makes a bowl of cereal"), *Time));
	}
	else if (!Time.Compare("Midday"))
	{
		//Execute the Midday routine
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("It is %s, so FreakyAllen's right eye starts to twitch"), *Time));
	}
	else if (!Time.Compare("Evening"))
	{
		//Execute the Evening routine
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("It is %s, so FreakyAllen morphs into a blood suckingwogglesnort"), *Time));
	}
}

void AFreakyAllen::SetClockTower(AClockTower* myClockTower)
{
	//Log Error if the passed Clock Tower is NULL
	if (!myClockTower) { UE_LOG(LogTemp, Error, TEXT("SetClockTower(): myClockTower is NULL, make sure it's initialized.")); return; }
	//Set the Clock Tower and Subscribe to that
	ClockTower = myClockTower;
	ClockTower->Subscribe(this);
}
