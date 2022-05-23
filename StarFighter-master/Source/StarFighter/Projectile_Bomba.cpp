// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Bomba.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AProjectile_Bomba::AProjectile_Bomba()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileBombaMesh(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));
	ProjectileMesh->SetStaticMesh(ProjectileBombaMesh.Object);

}

void AProjectile_Bomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = FVector(CurrentLocation.X + (ProjectileSpeed * DeltaTime), CurrentLocation.Y, CurrentLocation.Z);

	this->SetActorLocation(NewLocation);
	CurrentLocation = NewLocation;

}
