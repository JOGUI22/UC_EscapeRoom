// Copyright Jordi Casadevall Franco 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	owner->SetActorRotation(FRotator(0.f, openAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (GetTotalMassOfActorsOnPlate() > 50.f) { //TODO make into a parameter
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//Check if its time to close the door
	if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay) {
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.f;
	// Find allp the overlapping actors
	TArray<AActor*> overlappingActors;
	pressurePlate->GetOverlappingActors(OUT overlappingActors);

	// Iterate through all elements in the plate
	for (const auto* actor : overlappingActors)
	{
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *actor->GetName());
	}

	return totalMass;
}