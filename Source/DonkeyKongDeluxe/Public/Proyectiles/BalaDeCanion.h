// RUTA: Source/DonkeyKongDeluxe/Public/Proyectiles/BalaDeCanion.h

#pragma once

#include "CoreMinimal.h"
#include "Proyectiles/ProyectilBase.h" // (NUEVO) Incluimos al "padre" C++
#include "BalaDeCanion.generated.h"

/**
 * Bala de Cañón C++ Pura.
 * Hereda de AProyectilBase y anula la configuración de movimiento C++
 * para caer verticalmente (Gravedad Completa).
 */
UCLASS()
class DONKEYKONGDELUXE_API ABalaDeCanion : public AProyectilBase
{
	GENERATED_BODY()

public:
	ABalaDeCanion();
};