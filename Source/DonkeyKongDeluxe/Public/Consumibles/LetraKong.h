// RUTA: Source/DonkeyKongDeluxe/Public/Consumibles/LetraKong.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LetraKong.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DONKEYKONGDELUXE_API ALetraKong : public AActor
{
	GENERATED_BODY()

public:
	ALetraKong();

protected:
	// Componentes C++ puros (vinculados en el constructor)
	UPROPERTY()
	USphereComponent* ColisionEsfera;

	// Dejamos este UPROPERTY para que puedas asignarle el mesh (K, O, N, G)
	// en el Blueprint híbrido, como dijiste.
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshLetra;

	// Callback C++ puro
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};