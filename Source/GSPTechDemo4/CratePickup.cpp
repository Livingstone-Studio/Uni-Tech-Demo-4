// Fill out your copyright notice in the Description page of Project Settings.


#include "CratePickup.h"
#include "ItemPickup.h"
#include "PoyPoyCharacter.h"
#include "Components/BoxComponent.h"
#include "SpawningRobot.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACratePickup::ACratePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACratePickup::BeginPlay()
{
	Super::BeginPlay();

	isThrown = false;

	exploding = false;

	droppedOff = false;

	explodeTimer = 0.0f;

}

void ACratePickup::OnImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (isThrown) 
	{
		if (isExplosive)
		{
			exploding = true;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Exploding");
		}
		else if (isDestroyOnImpact)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Bye");

			if (drop && !droppedOff)
			{
				FActorSpawnParameters spawnParams;

				spawnParams.Owner = this;

				FRotator rotator;

				FVector spawnLocation = GetActorLocation();

				UWorld* world = GetWorld();

				if (world) 
				{
				}

				droppedOff = true;
			}

			if (robot) 
			{
				robot->RemoveFromList(this);
			}

			Destroy();
		}
	}

	if (OverlappedComponent == collider) 
	{
		APoyPoyCharacter* target = Cast<APoyPoyCharacter>(OtherActor);

		if (target && isThrown)
		{
			target->Hit(GetVelocity()/4);
		}

		isThrown = false;

	}
}

void ACratePickup::SetupCollision()
{
	if (collider)
	{
		collider->OnComponentBeginOverlap.AddDynamic(this, &ACratePickup::OnImpact);
	}
}

// Called every frame
void ACratePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (exploding && isExplosive) 
	{
		explodeTimer += DeltaTime;

		if (explodeTimer > timeTillExplode) 
		{
			// Explode

			TArray<FHitResult> hits;

			FCollisionShape colSphere = FCollisionShape::MakeSphere(300.0f);

			FVector pos = GetActorLocation();

			DrawDebugSphere(GetWorld(), pos, colSphere.GetSphereRadius(), 50, FColor::Cyan, false, 1.0f);

			bool isHit = GetWorld()->SweepMultiByProfile(hits, pos, pos, FQuat::Identity, "", colSphere);

			if (isHit) 
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "ExplosiveHasHit");

				TArray<APoyPoyCharacter*> done;

				for (auto& hit : hits) 
				{
					APoyPoyCharacter* target = Cast<APoyPoyCharacter>(hit.Actor);

					if (target)
					{
						if (done.Num() > 0) 
						{
							bool ok = true;

							for (auto& t : done)
							{
								if (target == t) 
								{
									ok = false;
								}
							}

							if (ok) 
							{
								GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "HasHitTargets");
								target->Hit(FVector::ZeroVector);
								done.Add(target);
							}
						}
						else 
						{
							GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "HasHitTargets");
							target->Hit(FVector::ZeroVector);
							done.Add(target);
						}
					}
				}
			}

			// Destroy

			if (drop && !droppedOff)
			{
				FActorSpawnParameters spawnParams;

				spawnParams.Owner = this;

				FRotator rotator;

				FVector spawnLocation = GetActorLocation();

				UWorld* world = GetWorld();

				if (world)
				{
				}

				droppedOff = true;

			}

			if (robot)
			{
				robot->RemoveFromList(this);
			}

			Destroy();

		}
	}

}

