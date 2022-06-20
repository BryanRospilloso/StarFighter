// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlingShot.h"
#include "SpaceShipShot.h"
#include "ShootAdapter.generated.h"

class ASpaceShipShot;

UCLASS()
class STARFIGHTER_API AShootAdapter : public AActor, public ISlingShot
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShootAdapter();

private:

	UPROPERTY()
		ASpaceShipShot* Disparar;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Sling() override;

};
