// Fill out your copyright notice in the Description page of Project Settings.


#include "NoDollarsState.h"
#include "OldSchoolSlotMachine.h"

// Sets default values
ANoDollarsState::ANoDollarsState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANoDollarsState::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANoDollarsState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANoDollarsState::SetSlotMachine(class AOldSchoolSlotMachine* SlotMachine)
{
	//Set the Slot Machine of this state
	OldSchoolSlotMachine = SlotMachine;
}
void ANoDollarsState::InsertCoin()
{
	//Log the Insert Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("You cannot insert a casino coin, the machine is out of money"));
}
void ANoDollarsState::RejectCoin()
{
	//Log the Reject Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("You have not inserted a casino coin"));
}
void ANoDollarsState::PullLever()
{
	//Log the Pull Lever string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("You turned, but there is NO money in the machine"));
}
void ANoDollarsState::Payout()
{
	//Log the Payout string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("No money was paid out"));
}
void ANoDollarsState::RestockDollars()
{
	//Set the state to "No Coin State"
	OldSchoolSlotMachine->SetState(OldSchoolSlotMachine->GetNoCoinState());
}
FString ANoDollarsState::ToString()
{
	//Return the String of this state
	return "machine is out of cash";
}