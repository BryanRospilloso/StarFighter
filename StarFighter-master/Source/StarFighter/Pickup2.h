// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Pickup2.generated.h"

UCLASS()
class STARFIGHTER_API APickup2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup2();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickUp2Mesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CollisionComponent;

	bool bHit;

	UFUNCTION()
		void OnBeginOverlap(AActor* Pickup2Actor, AActor* OtherActor);

	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved,
			FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
