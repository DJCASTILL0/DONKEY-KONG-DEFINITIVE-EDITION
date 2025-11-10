// RUTA: Source/DonkeyKongDeluxe/Public/Enemigos/Octoprus.h

#pragma once

#include "CoreMinimal.h"
#include "Enemigos/EnemigoBase.h"
#include "Octoprus.generated.h"

class USphereComponent;

// (NUEVO) Enum C++ para los estados de IA
UENUM(BlueprintType)
enum class EOctoprusEstado : uint8
{
	Patrullando,
	Persiguiendo,
	Detenido
};

UCLASS()
class DONKEYKONGDELUXE_API AOctoprus : public AEnemigoBase
{
	GENERATED_BODY()

public:
	AOctoprus();

	// Anulamos (Override) el Tick C++ para nuestra IA personalizada
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	// --- Componentes C++ ---

	// (NUEVO) Esfera de detección para "alertar" al enemigo
	UPROPERTY()
	USphereComponent* ZonaDeteccion;

	// --- Variables de IA C++ (puras) ---
	EOctoprusEstado EstadoActual;
	float VelocidadPersecucion;
	float DuracionPersecucion;

	// --- Temporizador C++ ---
	FTimerHandle TimerHandle_Persecucion;

	// --- Funciones de IA C++ ---

	// Lógica de los estados
	void LogicaPatrulla(float DeltaTime);
	void LogicaPersecucion(float DeltaTime);
	void LogicaDetenido(float DeltaTime);

	// Transiciones de estado C++
	void EntrarEstadoPersecucion();
	void EntrarEstadoDetenido();

	// Callback C++ para la ZonaDeteccion
	UFUNCTION()
	void OnOverlapDeteccion(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Callback C++ para el Timer
	void TerminarPersecucion();
};