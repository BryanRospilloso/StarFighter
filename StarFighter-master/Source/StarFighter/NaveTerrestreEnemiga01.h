// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveTerrestre.h"
#include "Projectile.h"
#include "Projectile_Bala.h"
#include "NaveTerrestreEnemiga01.generated.h"

UCLASS()
class STARFIGHTER_API ANaveTerrestreEnemiga01 : public ANaveTerrestre
{
	GENERATED_BODY()

public:
    ANaveTerrestreEnemiga01();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
        TSubclassOf<AProjectile_Bala> Projectile_BalaEnemigo_BP;

    UWorld* ThisWorld;

    UPROPERTY(EditAnywhere)
        FVector Current_Velocity;

    FVector Current_Location;
    FRotator Current_Rotation;

    float TotalTime;
    float RandomStart;
    float TimeSinceLastShot;
    float fDestroyTimer;
    float fBurstDelay;

    bool bHit;
    bool bDead;
	
};
