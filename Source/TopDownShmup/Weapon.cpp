// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;

}

void AWeapon::OnStartFire() {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Pressed")));
    FireAC = PlayWeaponSound(FireLoopSound);
    MuzFX = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, RootComponent, TEXT("MuzzleFlashSocket"));

}


void AWeapon::OnStopFire() {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Released")));
    PlayWeaponSound(FireFinishSound);
    FireAC->Stop();
    MuzFX->DeactivateSystem();
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}


UAudioComponent* AWeapon::PlayWeaponSound(USoundCue* Sound)
{
    UAudioComponent* AC = NULL;
    if (Sound)
    {
        AC = UGameplayStatics::SpawnSoundAttached(Sound, RootComponent);
    }
    return AC;
}
