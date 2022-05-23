// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Bala.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AProjectile_Bala::AProjectile_Bala()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileBalaMesh(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));
	ProjectileMesh->SetStaticMesh(ProjectileBalaMesh.Object);

}

void AProjectile_Bala::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = FVector(CurrentLocation.X + (ProjectileSpeed * DeltaTime), CurrentLocation.Y, CurrentLocation.Z);

	this->SetActorLocation(NewLocation);
	CurrentLocation = NewLocation;

}
