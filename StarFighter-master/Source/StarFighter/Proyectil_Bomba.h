// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Proyectil.h"
#include "Proyectil_Bomba.generated.h"

UCLASS()
class STARFIGHTER_API AProyectil_Bomba : public AProyectil
{
	GENERATED_BODY()

public:
	AProyectil_Bomba();

	/** Function to handle the projectile hitting something */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
