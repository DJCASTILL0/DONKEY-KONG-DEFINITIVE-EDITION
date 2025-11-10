// RUTA: Source/DonkeyKongDeluxe/Public/Interactuables/BarrilLanzadorControlable.h

#pragma once

#include "CoreMinimal.h"
#include "Interactuables/BarrilLanzadorAutomatico.h"
#include "BarrilLanzadorControlable.generated.h"

/**
 * Barril C++ que el jugador puede controlar.
 * Hereda de ABarrilLanzadorAutomatico y desactiva el timer C++.
 */
UCLASS()
class DONKEYKONGDELUXE_API ABarrilLanzadorControlable : public ABarrilLanzadorAutomatico
{
	GENERATED_BODY()

public:
	ABarrilLanzadorControlable();
};