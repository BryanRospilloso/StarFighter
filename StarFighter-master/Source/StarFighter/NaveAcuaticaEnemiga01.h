// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAcuatica.h"
#include "Projectile.h"
#include "Projectile_Bomba.h"
#include "NaveAcuaticaEnemiga01.generated.h"

UCLASS()
class STARFIGHTER_API ANaveAcuaticaEnemiga01 : public ANaveAcuatica
{
	GENERATED_BODY()

public:
	ANaveAcuaticaEnemiga01();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
        TSubclassOf<AProjectile_Bomba> Projectile_BombaEnemigo_BP;

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

    UFUNCTION()
        void OnBeginOverlap(AActor* EnemigoActor, AActor* OtherActor);
	
};
