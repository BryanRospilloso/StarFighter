// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAerea.h"
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

    UFUNCTION()
        void FireMisil();

    /* Handler for the fire timer expiry */
    UFUNCTION()
        void ShotTimerExpired();

    /** Offset from the ships location to spawn projectiles */
    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        FVector GunOffset;

    /* How fast the weapon will fire */
    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        float FireRate;

    const FVector FireDirection = FVector(-90.f, 0.f, 0.0f).GetClampedToMaxSize(1.0f);
    const FRotator FireRotation = FireDirection.Rotation();

    UPROPERTY(EditAnywhere)
        FVector Current_Velocity;

    FVector Current_Location;
    FRotator Current_Rotation;

    float RandomStart;

    float TotalTime;

    float TimeSinceLastShot;

    UFUNCTION()
        virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved,
            FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

    bool bHit;
    bool bDead;

    UWorld* ThisWorld;

private:
    /* Flag to control firing  */
    uint32 bCanFire : 1;

    /** Handle for efficient management of ShotTimerExpired timer */
    FTimerHandle TimerHandle_ShotTimerExpired;


    //float FireForwardValue;
   // float FireRightValue;
	
};
