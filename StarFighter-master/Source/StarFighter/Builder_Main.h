// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Builder_Main.generated.h"

UCLASS()
class STARFIGHTER_API ABuilder_Main : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilder_Main();

private:
	//The Builder Actor
	UPROPERTY(VisibleAnywhere, Category = "Main")
		class ATurretGunBuilder* TurretBuilder;

	//The Mechanic Actor
	UPROPERTY(VisibleAnywhere, Category = "Main")
		class AGunMechanic* Mechanic;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
