// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Decorator.h"
#include "IncrementoVelocidad.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API AIncrementoVelocidad : public ADecorator
{
	GENERATED_BODY()

public:
	virtual int Speed() override;
	
};
