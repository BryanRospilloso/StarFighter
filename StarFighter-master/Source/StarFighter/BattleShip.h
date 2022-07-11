// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleShipStrategy.h"
#include "BattleShip.generated.h"

UCLASS()
class STARFIGHTER_API ABattleShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleShip();

private:
	//The current Battle Strategy
	IBattleShipStrategy* BattleStrategy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AlterManeuvers(AActor* myBattleStrategy);
	// Engage with the current Battle Strategy
	void Engage();

};
