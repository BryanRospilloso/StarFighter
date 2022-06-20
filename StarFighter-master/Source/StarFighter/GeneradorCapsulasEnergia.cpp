// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneradorCapsulasEnergia.h"
#include "CapsulaEnergia1.h"
#include "CapsulaVida1.h"

ACapsula* AGeneradorCapsulasEnergia::FabricarCapsula(FString NombreTipoCapsula)
{
    float rand1 = FMath::RandRange(-900, 900);
    float rand2 = FMath::RandRange(-900, 900);
    
    if (NombreTipoCapsula.Equals("Energia1")) {
        return GetWorld()->SpawnActor<ACapsulaEnergia1>(FVector(rand1, rand2, 75.0f), FRotator::ZeroRotator);
    }
    
    else if (NombreTipoCapsula.Equals("Vida1")) {
        return GetWorld()->SpawnActor<ACapsulaVida1>(FVector(rand1, rand2, 75.0f), FRotator::ZeroRotator);
    }

    return nullptr;
}

