// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"
#include "PoyPoyCharacter.h"
#include "Tree.h"

// Sets default values
AItemPickup::AItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
	activeTimer = 0.0f;

}

// Called every frame
void AItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (activeTimer > timeTillActive) 
	{
		inital = true;
	}
	else 
	{
		activeTimer += DeltaTime;
	}
}


void AItemPickup::SetupCollision()
{
	if (box)
	{
		box->OnComponentBeginOverlap.AddDynamic(this, &AItemPickup::OnImpact);
	}

}

void AItemPickup::OnImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (inital) 
	{
		APoyPoyCharacter* target = Cast<APoyPoyCharacter>(OtherActor);

		if (target)
		{
			target->PoyPoyTakeDamage(-30);

			if (tree)
			{
				tree->Remove(this);
			}

			Destroy();
		}
	}
}