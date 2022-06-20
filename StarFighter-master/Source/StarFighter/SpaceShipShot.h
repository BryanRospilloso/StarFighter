// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Proyectil_Bala.h"
#include "SpaceShipShot.generated.h"

UCLASS()
class STARFIGHTER_API ASpaceShipShot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShipShot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//ProjectileBala

	void FireWeaponBala();
	void StartFiringBala();
	void StopFiringBala();
	bool bBalaIsFiring;
	float FireBalaRate;
	float BalaTimeSinceLastShot;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProyectil_Bala> Proyectil_Bala_BP;

	UWorld* ThisWorld;

};
