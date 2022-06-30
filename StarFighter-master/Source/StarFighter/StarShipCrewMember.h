// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StarShipCrewMember.generated.h"

UCLASS()
class STARFIGHTER_API AStarShipCrewMember : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStarShipCrewMember();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Execute the passed Task
	void Task(const FString& Task);

public:
	//Execute the TurnLightsOut task
	void TurnLightsOut();
	//Execute the HeaveOutTriceUp task
	void HeaveOutTriceUp();
	//Execute the LibertyCall task
	void LibertyCall();
	//Execute the CrewMuster task
	void CrewMuster();
	//Execute the passed Tasks
	void Task(const TArray<FString>& Tasks);
	//Execute the member duty. It's pure virtual, so it doesn't need an implementation in this class
		virtual void Duty() PURE_VIRTUAL(AStarShipCrewMember::Duty, ;);
	//Return the member Title. It's pure virtual, so it doesn't need an implementation in this class
		virtual FString CrewTitle()
		PURE_VIRTUAL(AStarShipCrewMember::CrewTitle, return "";);
};
