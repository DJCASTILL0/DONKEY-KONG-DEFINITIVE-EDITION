// RUTA: Source/DonkeyKongDeluxe/Private/Enemigos/ZingerPatrulladorVertical.cpp

#include "Enemigos/ZingerPatrulladorVertical.h"
#include "TimerManager.h" // Para el Timer C++
#include "GameFramework/CharacterMovementComponent.h" // Para AddMovementInput

AZingerPatrulladorVertical::AZingerPatrulladorVertical()
{

	TiempoCambioDireccion = 3.0f;
	VelocidadVertical = 100.0f;
	DireccionVertical = 1.0f; // 1.0 = Arriba
}

void AZingerPatrulladorVertical::BeginPlay()
{

	Super::BeginPlay();

	// Iniciamos el Timer C++
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_CambioDireccion,
		this,
		&AZingerPatrulladorVertical::InvertirDireccionVertical,
		TiempoCambioDireccion,
		true); // true = Bucle
}

void AZingerPatrulladorVertical::Tick(float DeltaTime)
{
	
	AddMovementInput(FVector(0.f, 0.f, 1.f), DireccionVertical * VelocidadVertical * DeltaTime);
}

void AZingerPatrulladorVertical::InvertirDireccionVertical()
{
	DireccionVertical *= -1.0f;
}