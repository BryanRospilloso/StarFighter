// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TorretasBuilder.h"
#include "GunMechanic.generated.h"

UCLASS()
class STARFIGHTER_API AGunMechanic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunMechanic();

private:
	//The Builder Actor, that must be a TorretasBuilder
	ITorretasBuilder* TorretasBuilder;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Creates the building
	void ConstructTorretas();

	//Set the Builder Actor
	void SetTorretasBuilder(AActor* Builder);

	//Get the Torretas of the Builder
	class ATorretas* GetTorretas();

};
