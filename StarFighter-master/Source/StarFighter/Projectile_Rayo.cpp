// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Rayo.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AProjectile_Rayo::AProjectile_Rayo()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileRayoMesh(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));
	ProjectileMesh->SetStaticMesh(ProjectileRayoMesh.Object);

}

void AProjectile_Rayo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = FVector(CurrentLocation.X + (ProjectileSpeed * DeltaTime), CurrentLocation.Y, CurrentLocation.Z);

	this->SetActorLocation(NewLocation);
	CurrentLocation = NewLocation;

}
