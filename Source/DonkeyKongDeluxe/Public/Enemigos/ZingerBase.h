// RUTA: Source/DonkeyKongDeluxe/Public/Enemigos/ZingerBase.h

#pragma once

#include "CoreMinimal.h"
#include "Enemigos/EnemigoBase.h" // (IMPORTANTE) Debe incluir a su padre
#include "ZingerBase.generated.h"

/**
 * Clase Base C++ para Zinger (Avispa).
 * Es invencible y flota (MOVE_Flying).
 * Anula la patrulla base de AEnemigoBase.
 */
UCLASS(Abstract)
// (LA CORRECCIÓN)
// Debe heredar de AEnemigoBase, no de sí mismo.
class DONKEYKONGDELUXE_API AZingerBase : public AEnemigoBase
{
	GENERATED_BODY()

public:
	AZingerBase();

	// Anulamos (Override) el Tick C++ para detener la patrulla horizontal
	virtual void Tick(float DeltaTime) override;

protected:
	// Anulamos (Override) BeginPlay C++ para forzar el modo de vuelo
	virtual void BeginPlay() override;
};