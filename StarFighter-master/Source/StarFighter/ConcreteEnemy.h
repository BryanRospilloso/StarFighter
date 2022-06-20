// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "ConcreteEnemy.generated.h"

class UStaticMeshComponent;

UCLASS()
class STARFIGHTER_API AConcreteEnemy : public AActor, public IEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConcreteEnemy();

	UPROPERTY()
		UStaticMeshComponent* ConcreteEnemyMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Fight() override {}
	virtual int GetDamage() override { return 10; }
	virtual void Die() override {}

};
