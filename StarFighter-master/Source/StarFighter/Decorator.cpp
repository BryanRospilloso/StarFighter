// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorator.h"

// Sets default values
ADecorator::ADecorator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADecorator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADecorator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADecorator::Fight()
{
	this->Enemy->Fight();
}

int ADecorator::GetDamage()
{
	return this->Enemy->GetDamage();
}

void ADecorator::Die()
{
	this->Enemy->Die();
}

