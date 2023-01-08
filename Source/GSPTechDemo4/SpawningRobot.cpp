// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningRobot.h"
#include "CratePickup.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawningRobot::ASpawningRobot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawningRobot::BeginPlay()
{
	Super::BeginPlay();
	
	spawnTimer = 0.0f;

	defaultPosition = GetActorLocation();

	targettingDefault = true;
	active = false;
}

// Called every frame
void ASpawningRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	spawnTimer += DeltaTime;

	// Move to position

	FVector newpos;

	if (targettingDefault) 
	{
		newpos = UKismetMathLibrary::VInterpTo(GetActorLocation(), defaultPosition, DeltaTime, 4.0f);
	}
	else 
	{
		newpos = UKismetMathLibrary::VInterpTo(GetActorLocation(), defaultPosition + targetPosition, DeltaTime, 4.0f);
	}

	SetActorLocation(newpos);


	if (targettingDefault)
	{
		if ((FVector::Distance(GetActorLocation(), defaultPosition) < 0.5f) && active)
		{
			active = false;
		}
	}
	else
	{
		if ((FVector::Distance(GetActorLocation(), defaultPosition + targetPosition) < 0.5f) && active)
		{
			active = false;

			SpawnPickup();
		}
	}


	TrySpawningPickup();
}

void ASpawningRobot::TrySpawningPickup()
{
			// If can spawn
	if (spawnTimer > timeBetweenSpawns)
	{
		if (pickups.Num() > 0 && pickupsOnPitch.Num() < pickupLimit)
		{
			if (!active) 
			{
				targetPosition = FVector(FMath::RandRange(-arenaSize, arenaSize),
					FMath::RandRange(-arenaSize, arenaSize),
					0);

				targettingDefault = false;
				active = true;
			}
			
			spawnTimer = 0.0f;
		}
	}
}

void ASpawningRobot::SpawnPickup()
{
	UWorld* world = GetWorld();

	if (world)
	{
		FActorSpawnParameters spawnParams;

		spawnParams.Owner = this;

		FRotator rotator;

		FVector spawnLocation = GetActorLocation() + spawnOffset;

		pickupsOnPitch.Add(world->SpawnActor<ACratePickup>(pickups[FMath::RandRange(0, pickups.Num() - 1)], spawnLocation, rotator, spawnParams));

		pickupsOnPitch[pickupsOnPitch.Num() - 1]->robot = this;

		active = false;

		targettingDefault = true;
	}
}

void ASpawningRobot::RemoveFromList(ACratePickup* pickup)
{
	if (pickupsOnPitch.Contains(pickup)) 
	{
		pickupsOnPitch.Remove(pickup);
	}
}


