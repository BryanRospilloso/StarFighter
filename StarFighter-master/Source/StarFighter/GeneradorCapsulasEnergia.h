// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneradorCapsulas.h"
#include "GeneradorCapsulasEnergia.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API AGeneradorCapsulasEnergia : public AGeneradorCapsulas
{
	GENERATED_BODY()

public:
	virtual ACapsula* FabricarCapsula(FString NombreTipoCapsula) override;
	
};
