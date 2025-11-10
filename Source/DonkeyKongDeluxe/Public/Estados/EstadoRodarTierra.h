// RUTA: Source/DonkeyKongDeluxe/Public/Estados/EstadoRodarTierra.h
#pragma once

#include "CoreMinimal.h"
#include "Estados/PlayerBaseState.h"
#include "EstadoRodarTierra.generated.h"

UCLASS()
class DONKEYKONGDELUXE_API UEstadoRodarTierra : public UPlayerBaseState
{
	GENERATED_BODY()

private:
	const float DuracionMaximaRoll = 0.5f;
	float TiempoRollActual;
	float FriccionSueloOriginal;
	float FuerzaRoll;

public:
	UEstadoRodarTierra();

	// (LA CORRECCIÓN) La firma C++ ahora coincide con PlayerBaseState.h
	virtual void OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia = nullptr) override;

	virtual void OnExit() override;
	virtual void TickState(float DeltaTime) override;
	virtual void ManejarInputSalto() override {}
	virtual void ManejarInputRodar() override {}
	virtual bool EstaAtacando() const override;
};