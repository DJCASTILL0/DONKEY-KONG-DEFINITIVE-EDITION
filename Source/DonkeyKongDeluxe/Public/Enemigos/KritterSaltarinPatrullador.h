// RUTA: Source/DonkeyKongDeluxe/Public/Enemigos/KritterSaltarinPatrullador.h

#pragma once

#include "CoreMinimal.h"
#include "Enemigos/EnemigoBase.h"
#include "KritterSaltarinPatrullador.generated.h"

/**
 * Kritter que salta Y patrulla.
 * Hereda el Tick() de AEnemigoBase para patrullar.
 * Usa un Timer para saltar.
 */
UCLASS()
class DONKEYKONGDELUXE_API AKritterSaltarinPatrullador : public AEnemigoBase
{
	GENERATED_BODY()

public:
	AKritterSaltarinPatrullador();

protected:
	virtual void BeginPlay() override;

	// NO anulamos Tick(), para que herede la patrulla

	// Variables C++ puras
	float TiempoEntreSaltos;
	float FuerzaSalto;

	// Timer C++
	FTimerHandle TimerHandle_Salto;
	void IntentarSalto();
};