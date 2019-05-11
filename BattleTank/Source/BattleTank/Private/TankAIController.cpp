// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Tank_AI_Controller BeginPlay"));
    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank_AI_Controller can`t find Player tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank_AI_Controller found player: %s"), *(PlayerTank->GetName()));
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (GetPlayerTank())
    {
        AimToThePlayer();
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn)
    {
        return nullptr;
    }
    return Cast<ATank>(PlayerPawn);
}

void ATankAIController::AimToThePlayer()
{
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) { return; }
    
    FVector PlayerLocation = GetPlayerTank()->GetActorLocation();
    ControlledTank->AimAt(PlayerLocation);
}
