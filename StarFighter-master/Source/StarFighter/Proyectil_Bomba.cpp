// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil_Bomba.h"

AProyectil_Bomba::AProyectil_Bomba()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileBombaMesh(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Bomba Mesh"));
	ProjectileMesh->SetStaticMesh(ProjectileBombaMesh.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile Bomba");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProyectil_Bomba::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

}

void AProyectil_Bomba::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();

}
