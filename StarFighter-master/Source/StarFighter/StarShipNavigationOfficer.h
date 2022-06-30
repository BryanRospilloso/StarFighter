// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StarShipCrewMember.h"
#include "StarShipNavigationOfficer.generated.h"

UCLASS()
class STARFIGHTER_API AStarShipNavigationOfficer : public AStarShipCrewMember
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStarShipNavigationOfficer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Interface Duty function - Prints the Duty log
	virtual void Duty() override;
	//Interface Duty function - Returns the title
	virtual FString CrewTitle() override;
	
};
