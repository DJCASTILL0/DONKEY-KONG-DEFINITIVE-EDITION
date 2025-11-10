// RUTA: Source/DonkeyKongDeluxe/Public/Estrategias/DiddyKongStrategy.h

#pragma once

#include "CoreMinimal.h"
#include "Estrategias/PlayerStrategy.h"
#include "DiddyKongStrategy.generated.h"

UCLASS()
class DONKEYKONGDELUXE_API UDiddyKongStrategy : public UPlayerStrategy
{
	GENERATED_BODY()

public:
	// (CORREGIDO) Nombres de parámetros C++
	virtual void AjustarParametrosMovimiento() override;
	virtual void AplicarMallaEAnimacion(ADKCPlayerCharacter* PersonajeReferencia) override;
	virtual void EjecutarRodar(ADKCPlayerCharacter* PersonajeReferencia) override;
};