// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Projectile_Bala.generated.h"

UCLASS()
class STARFIGHTER_API AProjectile_Bala : public AProjectile
{
	GENERATED_BODY()

public:
	AProjectile_Bala();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
