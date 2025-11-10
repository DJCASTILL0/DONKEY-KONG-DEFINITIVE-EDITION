// RUTA: Source/DonkeyKongDeluxe/Public/Estados/EstadoReposo.h
#pragma once

#include "CoreMinimal.h"
#include "Estados/PlayerBaseState.h" 
#include "EstadoReposo.generated.h"

UCLASS()
class DONKEYKONGDELUXE_API UEstadoReposo : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	UEstadoReposo();

	virtual void OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia = nullptr) override;
	virtual void OnExit() override;
	virtual void TickState(float DeltaTime) override;
	virtual void ManejarInputSalto() override;
	virtual void ManejarInputRodar() override;

	// (LA CORRECCIÓN C++) Añadimos la declaración que faltaba
	virtual void ManejarInputMoverDerecha(float Valor) override;
};