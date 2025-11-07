// Fill out your copyright notice in the Description page of Project Settings.

// RUTA: Source/DonkeyKongDeluxe/Public/Estrategias/PlayerStrategy.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlayerStrategy.generated.h"

class ADKCPlayerCharacter; // Declaracion anticipada

UCLASS(Abstract)
class DONKEYKONGDELUXE_API UPlayerStrategy : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ADKCPlayerCharacter* Personaje;

public:
	// Contrato para la accion de Rodar (Roll)
	virtual void EjecutarRodar(ADKCPlayerCharacter* PersonajeReferencia) PURE_VIRTUAL(EjecutarRodar, );

	// Contrato para ajustar los parametros de movimiento (velocidad, salto, etc.)
	virtual void AjustarParametrosMovimiento() PURE_VIRTUAL(AjustarParametrosMovimiento, );

	void SetPersonaje(ADKCPlayerCharacter* PersonajeReferencia) { Personaje = PersonajeReferencia; }
};