// Fill out your copyright notice in the Description page of Project Settings.


#include "IncrementoVelocidad.h"

int AIncrementoVelocidad::Speed()
{
	Super::Speed();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("Incremento de la velocidad de la nave"));
	return Super::Speed() + 100;
}