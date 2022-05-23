// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Misil.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AProjectile_Misil::AProjectile_Misil()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMisilMesh(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));
	ProjectileMesh->SetStaticMesh(ProjectileMisilMesh.Object);

}

void AProjectile_Misil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = FVector(CurrentLocation.X + (ProjectileSpeed * DeltaTime), CurrentLocation.Y, CurrentLocation.Z);

	this->SetActorLocation(NewLocation);
	CurrentLocation = NewLocation;

}
