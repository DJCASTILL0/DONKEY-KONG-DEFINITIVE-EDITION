// RUTA: Source/DonkeyKongDeluxe/Public/Proyectiles/ProyectilBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProyectilBase.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS(Abstract)
class DONKEYKONGDELUXE_API AProyectilBase : public AActor
{
	GENERATED_BODY()

public:
	AProyectilBase();

protected:
	// --- Componentes C++ ---
	UPROPERTY()
	USphereComponent* ColisionEsfera;

	UPROPERTY()
	UStaticMeshComponent* MeshProyectil;

	// (IMPORTANTE) Lo dejamos VisibleAnywhere para que las clases C++ hijas
	// (como tu código) puedan acceder a él
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovimientoProyectil;

	// --- Lógica C++ ---

	// (LA CORRECCIÓN C++)
	// Añadimos 'virtual' para permitir que las clases hijas C++ (como Corona)
	// anulen (override) esta función.
	UFUNCTION()
	virtual void OnHitProyectil(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Variable C++ pura para el daño
	float Dano;
};