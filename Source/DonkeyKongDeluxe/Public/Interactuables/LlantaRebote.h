// RUTA: Source/DonkeyKongDeluxe/Public/Interactuables/LlantaRebote.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LlantaRebote.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class DONKEYKONGDELUXE_API ALlantaRebote : public AActor
{
	GENERATED_BODY()

public:
	ALlantaRebote();

protected:
	float FuerzaRebote;

	// (NUEVO) El Mesh SÓLIDO (Será la raíz)
	UPROPERTY()
	UStaticMeshComponent* MeshLlanta;

	// (NUEVO) La ZONA DE REBOTE (Trigger)
	UPROPERTY()
	UBoxComponent* ZonaRebote;

	// Callback de Overlap (Solo para la ZonaRebote)
	UFUNCTION()
	void OnOverlapLlanta(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};