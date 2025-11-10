// RUTA: Source/DonkeyKongDeluxe/Private/Enemigos/ZingerPatrulladorVertical.cpp

#include "Enemigos/ZingerPatrulladorVertical.h"
#include "TimerManager.h" // Para el Timer C++
#include "GameFramework/CharacterMovementComponent.h" // Para AddMovementInput

AZingerPatrulladorVertical::AZingerPatrulladorVertical()
{
	// 1. Hereda invencibilidad, gravedad 0 de ZingerBase

	// 2. Variables C++ puras
	TiempoCambioDireccion = 3.0f;
	VelocidadVertical = 100.0f;
	DireccionVertical = 1.0f; // 1.0 = Arriba
}

void AZingerPatrulladorVertical::BeginPlay()
{
	// Llamamos al BeginPlay del PADRE (ZingerBase)
	// para que configure la colisión C++ y el modo MOVE_Flying
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
	// Anulamos el Tick() de ZingerBase (que estaba vacío)

	// (NUEVO) Ahora que estamos en modo MOVE_Flying,
	// esta llamada C++ SÍ funcionará.
	AddMovementInput(FVector(0.f, 0.f, 1.f), DireccionVertical * VelocidadVertical * DeltaTime);
}

void AZingerPatrulladorVertical::InvertirDireccionVertical()
{
	DireccionVertical *= -1.0f;
}