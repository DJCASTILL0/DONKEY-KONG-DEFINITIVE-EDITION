// RUTA: Source/DonkeyKongDeluxe/Public/Estados/EstadoEnBarril.h

#pragma once

#include "CoreMinimal.h"
#include "Estados/PlayerBaseState.h"
#include "EstadoEnBarril.generated.h"

class USpringArmComponent;
class ABarrilLanzadorAutomatico; // (NUEVO) Declaración anticipada C++

/**
 * Estado C++ para cuando el jugador está "dentro" de un barril.
 * (Refactorizado) Ahora acepta input C++ para rotar y disparar.
 */
UCLASS()
class DONKEYKONGDELUXE_API UEstadoEnBarril : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	virtual void OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia) override;
	virtual void OnExit() override;

	// (MODIFICADO) Ya no bloqueamos el input C++
	virtual void TickState(float DeltaTime) override {}
	virtual void ManejarInputSalto() override; // <-- Implementado
	virtual void ManejarInputRodar() override {} // <-- Sigue bloqueado
	virtual bool EstaAtacando() const override { return false; }
	virtual void ManejarInputMoverArriba(float Valor) override; // <-- Implementado

	// (NUEVO) El input C++ MoverDerecha no está en la base, lo añadimos
	virtual void ManejarInputMoverDerecha(float Valor);

protected:
	UPROPERTY()
	AActor* BarrilAsociado;

	UPROPERTY()
	USpringArmComponent* BrazoCamaraGuardado;

	// (NUEVO) Variables C++ puras para la rotación
	float VelocidadRotacionBarril;
};