// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDownShmupPlayerController.h"
#include "TopDownShmup.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Math/Vector.h"

ATopDownShmupPlayerController::ATopDownShmupPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATopDownShmupPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateMouseLook();

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		//MoveToMouseCursor();
	}
}


void ATopDownShmupPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
    
    //Our new bindings here:
    InputComponent->BindAxis("MoveForward", this, &ATopDownShmupPlayerController::MoveForward);
    InputComponent->BindAxis("MoveRight", this,
        &ATopDownShmupPlayerController::MoveRight);
    

    
	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATopDownShmupPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATopDownShmupPlayerController::MoveToTouchLocation);
    
    //New Fire code:
    InputComponent->BindAction("Fire", IE_Pressed, this, &ATopDownShmupPlayerController::OnStartFire);
    InputComponent->BindAction("Fire", IE_Released, this, &ATopDownShmupPlayerController::OnStopFire);
    
}


void ATopDownShmupPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}


 
void ATopDownShmupPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}



void ATopDownShmupPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
        if (Distance > 120.0f)
		{
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}


void ATopDownShmupPlayerController::UpdateMouseLook() {
	APawn* const Pawn = GetPawn();
	if (Pawn) {
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit) {
			FVector VectorA = Pawn->GetActorLocation();
			FVector VectorB = Hit.ImpactPoint;
			FVector VectorC = VectorB - VectorA;

			VectorC.Z = 0.0f;

			VectorC.Normalize();

			FRotator hitResultRotator = VectorC.Rotation();

			Pawn->SetActorRotation(hitResultRotator);


		}
	}
}

/*
void ATopDownShmupPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ATopDownShmupPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
*/

//All move functions here:

void ATopDownShmupPlayerController::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        APawn* const Pawn = GetPawn();
        if (Pawn)
        {
            Pawn->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
        }
    }
}

void ATopDownShmupPlayerController::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        APawn* const Pawn = GetPawn();
        if (Pawn)
        {
            Pawn->AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
        }
    }
}

void ATopDownShmupPlayerController::OnStartFire()
{
    APawn* Pawn = GetPawn();
    if (Pawn)
    {
        ATopDownShmupCharacter *MyCharacter = Cast<ATopDownShmupCharacter>(Pawn);
        MyCharacter->OnStartFire();
    }
}


void ATopDownShmupPlayerController::OnStopFire()
{
    APawn* Pawn = GetPawn();
    if (Pawn)
    {
        ATopDownShmupCharacter *MyCharacter = Cast<ATopDownShmupCharacter>(Pawn);
        MyCharacter->OnStopFire();
    }
}
    


