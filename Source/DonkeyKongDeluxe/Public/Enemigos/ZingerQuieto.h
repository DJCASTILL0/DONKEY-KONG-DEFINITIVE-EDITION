// RUTA: Source/DonkeyKongDeluxe/Public/Enemigos/ZingerQuieto.h
#pragma once

#include "CoreMinimal.h"
#include "Enemigos/ZingerBase.h"
#include "ZingerQuieto.generated.h"

/**
 * Zinger C++ que se queda quieto.
 * Hereda la invencibilidad, el modo MOVE_Flying y el Tick() vacío de ZingerBase.
 */
UCLASS()
class DONKEYKONGDELUXE_API AZingerQuieto : public AZingerBase
{
	GENERATED_BODY()

public:
	AZingerQuieto();
};