// RUTA: Source/DonkeyKongDeluxe/Public/Componentes/ComponenteInventario.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComponenteInventario.generated.h"

// Delegado (Observador) para el HUD de bananas
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBananasCambiadas, int, TotalBananas);

// (NUEVO) Delegado (Observador) para el HUD de vidas
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVidasCambiadas, int, TotalVidas);


UCLASS(ClassGroup = (DKCComponentes), meta = (BlueprintSpawnableComponent))
class DONKEYKONGDELUXE_API UComponenteInventario : public UActorComponent
{
	GENERATED_BODY()

public:
	UComponenteInventario();

	// --- Delegados (Observadores) ---
	UPROPERTY()
	FOnBananasCambiadas EnBananasCambiadas;

	// (NUEVO)
	UPROPERTY()
	FOnVidasCambiadas EnVidasCambiadas;

	// --- Funciones Publicas ---
	void AnadirBanana();
	void AnadirLetraKONG(); // (NUEVO)

	// --- Getters ---
	int GetConteoBananas() const { return ConteoBananas; }
	int GetVidas() const { return Vidas; } // (NUEVO)
	int GetLetrasKONG() const { return ConteoLetrasKONG; } // (NUEVO)

protected:
	virtual void BeginPlay() override;

	// --- Variables C++ Puras (Sin UPROPERTY) ---
	int ConteoBananas;
	int Vidas;
	int ConteoLetrasKONG; // (NUEVO)

private:
	// --- Funciones Internas ---
	void GanarVida(); // (NUEVO)
};