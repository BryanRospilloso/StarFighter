// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subscriber.h"
#include "Morph.h"
#include "FreakyAllen.generated.h"

class AClockTower;

UCLASS()
class STARFIGHTER_API AFreakyAllen : public AActor, public ISubscriber, public IMorph
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFreakyAllen();

private:
	//The Clock Tower of this Subscriber
	UPROPERTY()
		AClockTower* ClockTower;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called when this Subscriber is destroyed, it will unsubscribe this from the Clock Tower
	virtual void Destroyed() override;

public:
	//Called when the Plublisher changed its state, it will execute this Subscriber routine
	virtual void Update(class APublisher* Publisher) override;
	//Execute this Subscriber routine
	virtual void Morph();
	//Set the Clock Tower of this Subscriber
	void SetClockTower(AClockTower* myClockTower);

};
