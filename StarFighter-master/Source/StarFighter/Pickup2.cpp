// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup2.h"
#include "NaveAereaJugador.h"

// Sets default values
APickup2::APickup2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PickUp2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUp2Mesh"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	PickUp2Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void APickup2::BeginPlay()
{
	Super::BeginPlay();

	bHit = false;

	OnActorBeginOverlap.AddDynamic(this, &APickup2::OnBeginOverlap);
	
}

// Called every frame
void APickup2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = this->GetActorLocation();
	NewLocation.X -= DeltaTime * 50.0f;
	NewLocation.Y -= DeltaTime * 50.0f;
	NewLocation.Z = 0;
	this->SetActorLocation(NewLocation);

	if (bHit)
	{
		this->Destroy();
	}

}

void APickup2::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	ANaveAereaJugador* Pickup2 = Cast<ANaveAereaJugador>(Other);
	Pickup2->CollectablePickup2();
	this->Destroy();

}

void APickup2::OnBeginOverlap(AActor* Pickup2Actor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Wall1") || OtherActor->ActorHasTag("Wall2") || OtherActor->ActorHasTag("Wall3") || OtherActor->ActorHasTag("Wall4"))
	{
		bHit = true;
	}

}

