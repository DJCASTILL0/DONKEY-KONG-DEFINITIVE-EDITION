// RUTA: Source/DonkeyKongDeluxe/Public/Interactuables/BarrilLanzadorAutomatico.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BarrilLanzadorAutomatico.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class ADKCPlayerCharacter;
class UArrowComponent;

UCLASS()
class DONKEYKONGDELUXE_API ABarrilLanzadorAutomatico : public AActor
{
	GENERATED_BODY()

public:
	ABarrilLanzadorAutomatico();

	// (LA CORRECCIÓN C++)
	// Movido de 'protected' a 'public' para que UEstadoEnBarril pueda llamarlo
	void LanzarJugador();

protected:
	virtual void BeginPlay() override;

	// --- Componentes C++ ---
	UPROPERTY()
	UStaticMeshComponent* MeshBarril;
	UPROPERTY()
	USphereComponent* ZonaOverlap;
	UPROPERTY()
	UArrowComponent* FlechaDeLanzamientoVertical;

	// --- Lógica C++ ---
	UFUNCTION()
	void OnOverlapBarril(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// --- Variables C++ Puras ---
	float FuerzaLanzamiento;
	float RetrasoLanzamiento;
	bool bEsAutomatico;
	// --- Referencias C++ ---
	FTimerHandle TimerHandle_Lanzamiento;

	UPROPERTY()
	ADKCPlayerCharacter* JugadorAtrapado;
};