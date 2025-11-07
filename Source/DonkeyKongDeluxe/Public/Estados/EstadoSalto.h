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

	virtual void OnEnter(ADKCPlayerCharacter* PersonajeReferencia) override;
	virtual void OnExit() override;
	virtual void TickState(float DeltaTime) override;

	// Bloqueamos saltar y rodar en el aire
	virtual void ManejarInputSalto() override {}
	virtual void ManejarInputRodar() override {}
};