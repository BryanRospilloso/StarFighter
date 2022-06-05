// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil_Misil.h"

AProyectil_Misil::AProyectil_Misil()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMisilMesh(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Misil Mesh"));
	ProjectileMesh->SetStaticMesh(ProjectileMisilMesh.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile Misil");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProyectil_Misil::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

}

void AProyectil_Misil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();

}
