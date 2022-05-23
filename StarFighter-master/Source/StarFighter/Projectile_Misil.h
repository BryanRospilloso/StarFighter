// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Projectile_Misil.generated.h"

UCLASS()
class STARFIGHTER_API AProjectile_Misil : public AProjectile
{
	GENERATED_BODY()

public:
	AProjectile_Misil();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
