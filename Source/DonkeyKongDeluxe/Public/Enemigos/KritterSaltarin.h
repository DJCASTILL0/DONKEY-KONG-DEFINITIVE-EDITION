// RUTA: Source/DonkeyKongDeluxe/Public/Enemigos/KritterSaltarin.h

#pragma once

#include "CoreMinimal.h"
#include "Enemigos/EnemigoBase.h"
#include "KritterSaltarin.generated.h"


UCLASS()
class DONKEYKONGDELUXE_API AKritterSaltarin : public AEnemigoBase
{
	GENERATED_BODY()

public:
	AKritterSaltarin();

protected:
	// Anulamos (Override) BeginPlay para iniciar el timer
	virtual void BeginPlay() override;

	// Anulamos (Override) Tick para DETENER la logica de patrulla
	virtual void Tick(float DeltaTime) override;

	// Variables C++ puras para el salto (sin UPROPERTY)
	float TiempoEntreSaltos;
	float FuerzaSalto;

	// El manejador del Timer C++
	FTimerHandle TimerHandle_Salto;

	// La funcion que llamara el Timer
	void IntentarSalto();
};