// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton_Main.h"
#include "NaveNodrizaAereaEnemiga.h"

// Sets default values
ASingleton_Main::ASingleton_Main()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASingleton_Main::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i <= 4; i++)
	{
		ANaveNodrizaAereaEnemiga* SpawnedInventory = GetWorld()->SpawnActor<ANaveNodrizaAereaEnemiga>(ANaveNodrizaAereaEnemiga::StaticClass());
		if (SpawnedInventory)
		{
			Inventory = SpawnedInventory;
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("%s has been created"), *Inventory->GetName()));
		}
	}
	
}

// Called every frame
void ASingleton_Main::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

