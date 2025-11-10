// RUTA: Source/DonkeyKongDeluxe/Public/Estados/EstadoSalto.h
#pragma once

#include "CoreMinimal.h"
#include "Estados/PlayerBaseState.h"
#include "EstadoSalto.generated.h"

UCLASS()
class DONKEYKONGDELUXE_API UEstadoSalto : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	UEstadoSalto();
	virtual void OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia = nullptr) override;
	virtual void OnExit() override;
	virtual void TickState(float DeltaTime) override;

	virtual void ManejarInputSalto() override {}
	virtual void ManejarInputRodar() override {}

	// (LA CORRECCIÓN C++) Añadimos la declaración que faltaba
	virtual void ManejarInputMoverDerecha(float Valor) override;
};