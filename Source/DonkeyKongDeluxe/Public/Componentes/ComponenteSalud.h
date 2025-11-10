// RUTA: Source/DonkeyKongDeluxe/Public/Componentes/ComponenteSalud.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComponenteSalud.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaludCambiada, float, SaludActual);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMuerte);


UCLASS(ClassGroup = (DKCComponentes), meta = (BlueprintSpawnableComponent))
class DONKEYKONGDELUXE_API UComponenteSalud : public UActorComponent
{
	GENERATED_BODY()

public:
	UComponenteSalud();

	// --- Variables C++ Puras ---
	float SaludMaxima;
	float SaludActual;
	bool bPuedeSerInvulnerable; // Para el Jugador
	bool bEsInvencible; // Para Zinger/Octoprus

	// --- Delegados (Observador) ---
	UPROPERTY(BlueprintAssignable)
	FOnSaludCambiada EnSaludCambiada;
	UPROPERTY(BlueprintAssignable)
	FOnMuerte EnMuerte;

	// --- Funciones Publicas ---
	void RecibirDanio(float DanioAplicado);
	FORCEINLINE float GetSaludActual() const { return SaludActual; }
	FORCEINLINE float GetSaludMaxima() const { return SaludMaxima; }

	// (NUEVO) Getter C++ para que el jugador sepa si el enemigo es invencible
	FORCEINLINE bool EsInvencible() const { return bEsInvencible; }

protected:
	virtual void BeginPlay() override;

	// --- Lógica de Invulnerabilidad ---
	bool bEsInvulnerable;
	float DuracionInvulnerabilidad;
	FTimerHandle TimerHandle_Invulnerabilidad;
	void TerminarInvulnerabilidad();
};