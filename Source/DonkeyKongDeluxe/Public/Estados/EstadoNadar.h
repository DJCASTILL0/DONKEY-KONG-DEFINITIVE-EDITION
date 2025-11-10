// RUTA: Source/DonkeyKongDeluxe/Public/Estados/EstadoNadar.h
#pragma once

#include "CoreMinimal.h"
#include "Estados/PlayerBaseState.h"
#include "EstadoNadar.generated.h"

UCLASS()
class DONKEYKONGDELUXE_API UEstadoNadar : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	// (LA CORRECCIÓN) La firma C++ ahora coincide con PlayerBaseState.h
	virtual void OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia = nullptr) override;

	virtual void OnExit() override;
	virtual void ManejarInputMoverArriba(float Valor) override;
	virtual void ManejarInputSalto() override {}
	virtual void ManejarInputRodar() override {}
	virtual bool EstaAtacando() const override { return false; }

private:
	float GravedadOriginal;
	float FriccionOriginal;
	bool bOrientacionOriginal;
};