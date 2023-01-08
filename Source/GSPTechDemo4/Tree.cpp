// Fill out your copyright notice in the Description page of Project Settings.


#include "Tree.h"
#include "ItemPickup.h"

// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATree::Remove(class AItemPickup* item)
{
	if (spawnPositionOnePickup == item) 
	{
		spawnPositionOnePickup = nullptr;
	}

	if (spawnPositionTwoPickup == item)
	{
		spawnPositionTwoPickup = nullptr;
	}
}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();

	regenTimer = 0.0f;
	
}

// Called every frame
void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!spawnPositionOnePickup || !spawnPositionTwoPickup) 
	{
		regenTimer += DeltaTime;

		if (regenTimer > maxRegenTime) 
		{
			UWorld* world = GetWorld();

			if (!spawnPositionOnePickup) 
			{
				if (world)
				{
					FActorSpawnParameters spawnParams;

					spawnParams.Owner = this;

					FRotator rotator;

					FVector spawnLocation = mesh->GetSocketLocation("SpawnPosOne");

					spawnPositionOnePickup = world->SpawnActor<AItemPickup>(heart, spawnLocation, rotator, spawnParams);

					spawnPositionOnePickup->tree = this;

				}
			}
			else if (!spawnPositionTwoPickup) 
			{
				if (world)
				{
					FActorSpawnParameters spawnParams;

					spawnParams.Owner = this;

					FRotator rotator;

					FVector spawnLocation = mesh->GetSocketLocation("SpawnPosTwo");

					spawnPositionTwoPickup = world->SpawnActor<AItemPickup>(heart, spawnLocation, rotator, spawnParams);

					spawnPositionTwoPickup->tree = this;

				}
			}

			regenTimer = 0.0f;
		}

	}
}

