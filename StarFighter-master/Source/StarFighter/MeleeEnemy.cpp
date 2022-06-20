// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"

void AMeleeEnemy::Fight()
{
	//Call the parent Fight function and log a message
	Super::Fight();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("El enemigo lanza fuertes golpes"));
}
int AMeleeEnemy::GetDamage()
{
	//Returns the base damage + 5
	return Super::GetDamage() + 5;
}

void AMeleeEnemy::Die()
{
	//Call the parent Die function al log a message
	Super::Die();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("El enemigo muere"));
}
