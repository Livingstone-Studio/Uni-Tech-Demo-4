// Fill out your copyright notice in the Description page of Project Settings.


#include "PoyPoyCharacter.h"
#include "PoyPoyChar.h"
#include "CratePickup.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"

// Sets default values
APoyPoyCharacter::APoyPoyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoyPoyCharacter::BeginPlay()
{
	Super::BeginPlay();

	isJumping = false;
	canMove = true;
	isHit = false;
	isDead = false;

	health = maxHealth;

	noMoveTimer = 0;
	hitTimer = 0;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	
}

// Called every frame
void APoyPoyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isJumping) 
	{
		Jump();
	}

	if (!canMove) 
	{
		noMoveTimer += DeltaTime;

		if (noMoveTimer > maxNoMoveTimer) 
		{
			canMove = true;
			noMoveTimer = 0;
		}
	}

	if (isHit)
	{
		hitTimer += DeltaTime;

		if (hitTimer > maxHitTimer)
		{
			isHit = false;
			hitTimer = 0;
		}
	}
}

// Called to bind functionality to input
void APoyPoyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APoyPoyCharacter::JumpCheck);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APoyPoyCharacter::JumpCheck);

	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &APoyPoyCharacter::TryPickup);

	PlayerInputComponent->BindAction("Power", IE_Pressed, this, &APoyPoyCharacter::Power);

	PlayerInputComponent->BindAxis("Forward", this, &APoyPoyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Horizontal", this, &APoyPoyCharacter::MoveHorizontal);
}

void APoyPoyCharacter::SetupCollider()
{
	if (pickupCollider)
	{
		pickupCollider->OnComponentBeginOverlap.AddDynamic(this, &APoyPoyCharacter::CheckOverlapForPickups);
		pickupCollider->OnComponentEndOverlap.AddDynamic(this, &APoyPoyCharacter::RemoveOverlappingPickups);
	}
}

void APoyPoyCharacter::MoveForward(float value)
{
	if (canMove && !isHit && !isDead) 
	{
		FRotator rot = Controller->GetControlRotation();
		FRotator yaw(0, rot.Yaw, 0);
		FVector direction = FRotationMatrix(yaw).GetUnitAxis(EAxis::X);

		AddMovementInput(direction, -value);
	}
}

void APoyPoyCharacter::MoveHorizontal(float value)
{
	if (canMove && !isHit && !isDead)
	{
		FRotator rot = Controller->GetControlRotation();
		FRotator yaw(0, rot.Yaw, 0);
		FVector direction = FRotationMatrix(yaw).GetUnitAxis(EAxis::Y);

		AddMovementInput(direction, -value);
	}
}

void APoyPoyCharacter::JumpCheck()
{
	if (isJumping) 
	{
		isJumping = false;
	}
	else
	{
		isJumping = true;
	}
}

void APoyPoyCharacter::TryPickup()
{
	if (isDead) return;

	if (heldPickup) 
	{
		canMove = false;
	}
	else if (!heldPickup && highlightedPickup)
	{
		canMove = false;
	}
}

void APoyPoyCharacter::Throw(float strength)
{
	isHolding = false;

	heldPickup->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	if (heldPickup->box)
	{
		heldPickup->box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		heldPickup->box->SetSimulatePhysics(true);

		heldPickup->box->AddImpulse(GetActorForwardVector() * strength * heldPickup->box->GetMass(), NAME_None, true);

		heldPickup->isThrown = true;
	}

	heldPickup = nullptr;
}

void APoyPoyCharacter::Pickup()
{
	if (heldPickup || !highlightedPickup) return;

	heldPickup = highlightedPickup;

	if (!heldPickup) return;

	if (heldPickup->box)
	{
		heldPickup->box->SetSimulatePhysics(false);

		heldPickup->box->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		heldPickup->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("PickupSocket"));
	}

	isHolding = true;
}

void APoyPoyCharacter::Hit(FVector velocity)
{
	UCharacterMovementComponent* movement = GetCharacterMovement();

	movement->AddImpulse(velocity, true);

	PoyPoyTakeDamage(30);

	isHit = true;
}

void APoyPoyCharacter::Power()
{
	if (heldPickup) 
	{
		heldPickup->Destroy();

		SpawnPickupInHand(bomb);

		canMove = false;
	}
}

void APoyPoyCharacter::PoyPoyTakeDamage(int amount)
{
	health -= amount;

	if (health > maxHealth) 
	{
		health = maxHealth;
	}

	if (health <= 0) 
	{
		isDead = true;
		health = 0;
	}
}

void APoyPoyCharacter::SpawnPickupInHand(TSubclassOf<class ACratePickup> pickup)
{
	if (pickup)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			FActorSpawnParameters spawnParams;

			spawnParams.Owner = this;

			FRotator rotator;

			FVector spawnLocation = this->GetMesh()->GetSocketLocation("PickupSocket");

			heldPickup = world->SpawnActor<ACratePickup>(pickup, spawnLocation, rotator, spawnParams);

			if (heldPickup->box)
			{
				heldPickup->box->SetSimulatePhysics(false);

				heldPickup->box->SetCollisionEnabled(ECollisionEnabled::NoCollision);

				heldPickup->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("PickupSocket"));
			}
		}
	}
}

void APoyPoyCharacter::CheckOverlapForPickups(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	highlightedPickup = Cast<ACratePickup>(OtherActor);
}

void APoyPoyCharacter::RemoveOverlappingPickups(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACratePickup* pickup = Cast<ACratePickup>(OtherActor);

	if (highlightedPickup == pickup) 
	{
		highlightedPickup = nullptr;
	}
}
