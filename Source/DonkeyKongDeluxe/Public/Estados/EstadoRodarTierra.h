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

	// Variable para guardar la friccion original
	float FriccionSueloOriginal;

	// Fuerza del impulso
	float FuerzaRoll;

public:
	UEstadoRodarTierra();

	virtual void OnEnter(ADKCPlayerCharacter* PersonajeReferencia) override;
	virtual void OnExit() override;
	virtual void TickState(float DeltaTime) override;

	virtual void ManejarInputSalto() override {}
	virtual void ManejarInputRodar() override {}
};