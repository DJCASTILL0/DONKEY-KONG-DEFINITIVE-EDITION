// RUTA: Source/DonkeyKongDeluxe/Public/Componentes/ComponenteSalud.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComponenteSalud.generated.h"

// Los delegados NECESITAN UPROPERTY para funcionar con el sistema de eventos de Unreal.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaludCambiada, float, SaludActual);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMuerte);

UCLASS(ClassGroup = (DKCComponentes), meta = (BlueprintSpawnableComponent))
class DONKEYKONGDELUXE_API UComponenteSalud : public UActorComponent
{
	GENERATED_BODY()

public:
	UComponenteSalud();

	// Estas son ahora variables C++ puras. No apareceran en el editor.
	float SaludMaxima;
	float SaludActual;

	// Delegados (Observador) - Necesitan UPROPERTY para el sistema de reflexión
	UPROPERTY()
	FOnSaludCambiada EnSaludCambiada;

	UPROPERTY()
	FOnMuerte EnMuerte;

	// Funciones publicas
	void RecibirDanio(float DanioAplicado);
	FORCEINLINE float GetSaludActual() const { return SaludActual; }
	FORCEINLINE float GetSaludMaxima() const { return SaludMaxima; }

protected:
	virtual void BeginPlay() override;
};