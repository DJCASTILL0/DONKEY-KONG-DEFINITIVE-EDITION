// RUTA: Source/DonkeyKongDeluxe/Public/Enemigos/KingKRool.h

#pragma once

#include "CoreMinimal.h"
#include "Enemigos/EnemigoBase.h"
#include "KingKRool.generated.h"

// (NUEVO) El enum C++ para nuestra Máquina de Estados (FSM)
UENUM(BlueprintType)
enum class EEstadoJefe : uint8
{
	Fase1_LanzandoCorona, // Vulnerable
	Fase2_LluviaDeBalas // Invulnerable y Patrullando
};

UCLASS()
class DONKEYKONGDELUXE_API AKingKRool : public AEnemigoBase
{
	GENERATED_BODY()

public:
	AKingKRool();

	// Anulamos (Override) el Tick C++ para nuestra IA personalizada
	virtual void Tick(float DeltaTime) override;

protected:
	// Anulamos (Override) BeginPlay C++
	virtual void BeginPlay() override;

	// --- Estado de IA C++ ---
	EEstadoJefe EstadoActualJefe;

	// --- Lógica de Fase 1 (Corona) ---
	float TiempoEntreLanzamientosCorona;
	FTimerHandle TimerHandle_LanzamientoCorona;
	void LanzarCorona();

	// --- Lógica de Fase 2 (Lluvia de Balas) ---
	float DuracionFase2;
	float TiempoEntreBalas;
	FTimerHandle TimerHandle_DuracionFase2;
	FTimerHandle TimerHandle_LluviaDeBalas;
	void GenerarBalaDeCanion();

	// --- Funciones de Transición de Estado C++ ---
	void EntrarFase1();
	void EntrarFase2();
	void TerminarFase2(); // Callback C++ del Timer

	// (NUEVO) Callback C++ que se suscribe a ComponenteSalud->EnDanoRecibido
	UFUNCTION()
	void AlRecibirDano();

	// (NUEVO) Lógica C++ de Fase 1
	void LogicaFase1(float DeltaTime);
	// (NUEVO) Lógica C++ de Fase 2
	void LogicaFase2(float DeltaTime);
};