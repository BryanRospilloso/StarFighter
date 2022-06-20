// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootAdapter.h"

// Sets default values
AShootAdapter::AShootAdapter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShootAdapter::BeginPlay()
{
	Super::BeginPlay();

	Disparar = GetWorld()->SpawnActor<ASpaceShipShot>(ASpaceShipShot::StaticClass());
}

// Called every frame
void AShootAdapter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShootAdapter::Sling()
{
	Disparar->StartFiringBala();
}

