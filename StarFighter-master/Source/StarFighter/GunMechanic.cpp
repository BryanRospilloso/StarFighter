// Fill out your copyright notice in the Description page of Project Settings.


#include "GunMechanic.h"
#include "Torretas.h"

// Sets default values
AGunMechanic::AGunMechanic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGunMechanic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunMechanic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunMechanic::SetTorretasBuilder(AActor* Builder)
{
	//Cast the passed Actor and set the Builder
	TorretasBuilder = Cast<ITorretasBuilder>(Builder);

	if (!TorretasBuilder) //Log Error if cast fails
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("Invalid Cast! See Output log for more details")));
		UE_LOG(LogTemp, Error, TEXT("SetTorretasBuilder(): The Actor is not a TorretasBuilder! Are you sure that the Actor implements that interface?"));
	}

}

ATorretas* AGunMechanic::GetTorretas()
{
	if (TorretasBuilder)
	{
		//Returns the Lodging of the Builder
		return TorretasBuilder->GetTorretas();
	}
	//Log if the Builder is NULL
	UE_LOG(LogTemp, Error, TEXT("GetTorretas(): Return nullptr"));
	return nullptr;
}

void AGunMechanic::ConstructTorretas()
{
	//Log if the Builder is NULL
	if (!TorretasBuilder)
	{
		UE_LOG(LogTemp, Error, TEXT("ConstructTorretas(): TorretasBuilder is NULL, make sure it's inicialized."));
		return;
	}

	//Creates the buildings
	TorretasBuilder->BuildSoporteTorreta();
	TorretasBuilder->BuildCuerpoTorreta();
	TorretasBuilder->BuildArmasTorreta();
}

