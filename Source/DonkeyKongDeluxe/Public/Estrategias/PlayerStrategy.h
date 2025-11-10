// RUTA: Source/DonkeyKongDeluxe/Public/Estrategias/PlayerStrategy.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlayerStrategy.generated.h"

class ADKCPlayerCharacter;

UCLASS(Abstract)
class DONKEYKONGDELUXE_API UPlayerStrategy : public UObject
{
	GENERATED_BODY()

protected:
	// Variable Miembro C++
	UPROPERTY()
	ADKCPlayerCharacter* Personaje;

public:
	// --- Contrato C++ ---

	// (CORREGIDO) Cambiamos el nombre del parámetro
	virtual void AjustarParametrosMovimiento() PURE_VIRTUAL(AjustarParametrosMovimiento, );
	virtual void EjecutarRodar(ADKCPlayerCharacter* PersonajeReferencia) PURE_VIRTUAL(EjecutarRodar, );

	// (CORREGIDO) Cambiamos el nombre del parámetro C++
	virtual void AplicarMallaEAnimacion(ADKCPlayerCharacter* PersonajeReferencia) PURE_VIRTUAL(AplicarMallaEAnimacion, );

	void SetPersonaje(ADKCPlayerCharacter* PersonajeReferencia) { Personaje = PersonajeReferencia; }
};