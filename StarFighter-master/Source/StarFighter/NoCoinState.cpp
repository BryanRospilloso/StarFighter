// Fill out your copyright notice in the Description page of Project Settings.


#include "NoCoinState.h"
#include "OldSchoolSlotMachine.h"

// Sets default values
ANoCoinState::ANoCoinState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANoCoinState::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANoCoinState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANoCoinState::SetSlotMachine(class AOldSchoolSlotMachine* SlotMachine)
{
	//Set the Slot Machine of this state
	OldSchoolSlotMachine = SlotMachine;
}
void ANoCoinState::InsertCoin()
{
	//Log the Insert Coin string and set the state to "Coin Inserted State"
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("You inserted a casino coin"));
	OldSchoolSlotMachine->SetState(OldSchoolSlotMachine->GetCoinInsertedState());
}
void ANoCoinState::RejectCoin()
{
	//Log the Reject Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("You haven't inserted a casino coin"));
}
void ANoCoinState::PullLever()
{
	//Log the Pull Lever string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("You turned, but there's no casino coin"));
}
void ANoCoinState::Payout()
{
	//Log the Payout string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("You need to pay first"));
}
void ANoCoinState::RestockDollars() { /*Nothing*/ }
FString ANoCoinState::ToString()
{
	//Return the String of this state
	return "waiting for a casino coin";
}