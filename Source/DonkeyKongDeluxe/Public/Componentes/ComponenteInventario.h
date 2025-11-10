// RUTA: Source/DonkeyKongDeluxe/Public/Componentes/ComponenteInventario.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComponenteInventario.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBananasCambiadas, int, TotalBananas);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVidasCambiadas, int, TotalVidas);

UCLASS(ClassGroup = (DKCComponentes), meta = (BlueprintSpawnableComponent))
class DONKEYKONGDELUXE_API UComponenteInventario : public UActorComponent
{
	GENERATED_BODY()

public:
	UComponenteInventario();

	// --- Delegados (Observador) ---
	UPROPERTY()
	FOnBananasCambiadas EnBananasCambiadas;
	UPROPERTY()
	FOnVidasCambiadas EnVidasCambiadas;

	// --- Funciones Publicas (Interfaz C++ para Consumibles) ---
	void AnadirBanana(); // (Para la banana de 1)
	void AnadirLetraKONG();

	// (NUEVO) Para la BananaMD
	void AnadirBananas(int Cantidad);

	// (NUEVO) Para los Globos
	void AnadirVidas(int Cantidad);

	// --- Getters ---
	int GetConteoBananas() const { return ConteoBananas; }
	int GetVidas() const { return Vidas; }
	int GetLetrasKONG() const { return ConteoLetrasKONG; }

protected:
	virtual void BeginPlay() override;

	// --- Variables C++ Puras ---
	int ConteoBananas;
	int Vidas;
	int ConteoLetrasKONG;

private:
	// --- Funciones Internas C++ ---
	void GanarVida(); // (Ahora solo añade 1 vida)
};