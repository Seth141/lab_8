// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "AssultWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API AAssultWeapon : public AWeapon
{
	GENERATED_BODY()
    virtual void OnStartFire() override;
    virtual void OnStopFire() override;
	
};
