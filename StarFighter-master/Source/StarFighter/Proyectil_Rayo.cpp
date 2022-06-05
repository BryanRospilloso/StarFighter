// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil_Rayo.h"

AProyectil_Rayo::AProyectil_Rayo()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileRayoMesh(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Rayo Mesh"));
	ProjectileMesh->SetStaticMesh(ProjectileRayoMesh.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile Rayo");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProyectil_Rayo::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

}

void AProyectil_Rayo::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();

}
