// RUTA: Source/DonkeyKongDeluxe/Public/Proyectiles/CoronaProyectil.h

#pragma once

#include "CoreMinimal.h"
#include "Proyectiles/ProyectilBase.h"
#include "CoronaProyectil.generated.h"

class AKingKRool; // (NUEVO) Referencia C++ al Jefe

UCLASS()
class DONKEYKONGDELUXE_API ACoronaProyectil : public AProyectilBase
{
	GENERATED_BODY()

public:
	ACoronaProyectil();

	// Anulamos (Override) el Tick C++ para nuestra lógica de bumerán
	virtual void Tick(float DeltaTime) override;

	// (NUEVO) Función C++ para iniciar el movimiento
	void IniciarBumeran(AKingKRool* Jefe);

protected:
	// Anulamos (Override) el BeginPlay C++
	virtual void BeginPlay() override;

	// Anulamos (Override) el OnHit C++
	virtual void OnHitProyectil(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	// --- Variables C++ Puras (basadas en tu código C++) ---
	FVector UbicacionInicial;
	float DistanciaMaximaRecorrido;
	bool bEstaRegresando;

	// Referencia C++ al Jefe
	UPROPERTY()
	AKingKRool* JefeKRool;
};