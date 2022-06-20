// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneradorCapsulasArmas.h"
#include "CapsulaArma1.h"
#include "CapsulaEscudo1.h"

ACapsula* AGeneradorCapsulasArmas::FabricarCapsula(FString NombreTipoCapsula)
{   
    float rand1 = FMath::RandRange(-900, 900);
    float rand2 = FMath::RandRange(-900, 900);

    if (NombreTipoCapsula.Equals("Arma1")) {
        return GetWorld()->SpawnActor<ACapsulaArma1>(FVector(rand1, rand2, 75.0f), FRotator::ZeroRotator);
    }

    else if (NombreTipoCapsula.Equals("Escudo1")) {
        return GetWorld()->SpawnActor<ACapsulaEscudo1>(FVector(rand1, rand2, 75.0f), FRotator::ZeroRotator);
    }

    return nullptr;
}

