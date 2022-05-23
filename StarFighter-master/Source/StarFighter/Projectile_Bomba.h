// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Projectile_Bomba.generated.h"

UCLASS()
class STARFIGHTER_API AProjectile_Bomba : public AProjectile
{
	GENERATED_BODY()

public:
	AProjectile_Bomba();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
