// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Proyectil_Bala.h"
#include "NaveNodrizaAereaEnemiga.generated.h"

class UStaticMeshComponent;

UCLASS()
class STARFIGHTER_API ANaveNodrizaAereaEnemiga : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANaveNodrizaAereaEnemiga();

	UPROPERTY()
		ANaveNodrizaAereaEnemiga* Instance;

	UPROPERTY()
		UStaticMeshComponent* NaveNodriza;

	UPROPERTY(EditAnywhere)
		FVector Current_Velocity;

	FVector Current_Location;
	FRotator Current_Rotation;

	float RandomStart;
	float TotalTime;
	float Size;
	int Disparo;
	float FireForwardValue;
	float FireRightValue;

	bool bHit;

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	float TimeSinceLastShot;
	float fBurstDelay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
