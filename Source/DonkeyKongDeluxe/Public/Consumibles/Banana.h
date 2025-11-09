// RUTA: Source/DonkeyKongDeluxe/Public/Consumibles/Banana.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Banana.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DONKEYKONGDELUXE_API ABanana : public AActor
{
	GENERATED_BODY()

public:
	ABanana();

protected:
	// Se llama cuando el juego comienza
	virtual void BeginPlay() override;

	// Componentes (Necesitan UPROPERTY para Recoleccion de Basura)
	UPROPERTY()
	USphereComponent* ColisionEsfera;
	UPROPERTY()
	UStaticMeshComponent* MeshBanana;

	// Callback (Necesita UFUNCTION para delegados)
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};