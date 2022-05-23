// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MC_ActionInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UMC_ActionInterface : public UInterface
{
	GENERATED_BODY()
};

class STARFIGHTER_API IMC_ActionInterface
{
	GENERATED_BODY()

public:
    IMC_ActionInterface();

protected:
    virtual void BeginPlay();

public:
    virtual void Tick(float DeltaTime);

    //UPROPERTY(EditAnywhere)
        //TSubclassOf<AProjectile_BalaEnemigo> Projectile_BalaEnemigo_BP;

    UWorld* ThisWorld;

    //UPROPERTY(EditAnywhere)
        //FVector Current_Velocity;

    FVector Current_Location;
    FRotator Current_Rotation;

    float TotalTime;
    float RandomStart;
    float TimeSinceLastShot;
    float fDestroyTimer;
    float fBurstDelay;

    bool bHit;
    bool bDead;

    //UFUNCTION()
       // void OnBeginOverlap(AActor* EnemigoActor, AActor* OtherActor);

};
