// Fill out your copyright notice in the Description page of Project Settings.

#include "AIDwarfController.h"
#include "DwarfCharacter.h"

// Sets default values
ADwarfCharacter::ADwarfCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAIDwarfController::StaticClass();


}