// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Proyectil_Bala.h"
#include "Shoot.generated.h"

UCLASS()
class STARFIGHTER_API AShoot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
