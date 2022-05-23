// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAerea.h"
#include "Projectile.h"
#include "Projectile_Misil.h"
#include "NaveAereaEnemiga01.generated.h"

UCLASS()
class STARFIGHTER_API ANaveAereaEnemiga01 : public ANaveAerea
{
	GENERATED_BODY()

public:
    ANaveAereaEnemiga01();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
        TSubclassOf<AProjectile_Misil> Projectile_MisilEnemigo_BP;

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
