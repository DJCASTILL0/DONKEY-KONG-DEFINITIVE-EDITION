// RUTA: Source/DonkeyKongDeluxe/Public/Enemigos/Kritter.h

#pragma once

#include "CoreMinimal.h"
#include "Enemigos/EnemigoBase.h"
#include "Kritter.generated.h"

/**
 * Kritter Básico.
 * Hereda toda la lógica de patrulla (Tick) y salud de AEnemigoBase.
 * Solo necesitamos asignarle un mesh en C++.
 */
UCLASS()
class DONKEYKONGDELUXE_API AKritter : public AEnemigoBase
{
	GENERATED_BODY()

public:
	AKritter();
};