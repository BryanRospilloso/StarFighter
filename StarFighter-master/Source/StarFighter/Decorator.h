// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "Decorator.generated.h"

UCLASS()
class STARFIGHTER_API ADecorator : public AActor, public IEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADecorator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	IEnemy* Enemy;

public:
	virtual void Fight() override;
	virtual int GetDamage() override;
	virtual void Die() override;

	void SetEnemy(IEnemy* _Enemy) { Enemy = _Enemy; }
	IEnemy* GetEnemy() { return Enemy; }

};
