// Copyright Jordi Casadevall Franco 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float openAngle = -90.0f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;

	AActor* owner = nullptr; //The owning door

	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 1.f;

	float lastDoorOpenTime;

	//Return full mass in plate
	float GetTotalMassOfActorsOnPlate();
};
