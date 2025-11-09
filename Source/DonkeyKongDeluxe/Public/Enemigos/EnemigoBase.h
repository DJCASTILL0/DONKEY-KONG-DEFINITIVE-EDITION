// RUTA: Source/DonkeyKongDeluxe/Public/Enemigos/EnemigoBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemigoBase.generated.h"

class UComponenteSalud; // Declaracion anticipada

UCLASS()
class DONKEYKONGDELUXE_API AEnemigoBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemigoBase();
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE UComponenteSalud* GetComponenteSalud() const { return ComponenteSalud; }

protected:
	virtual void BeginPlay() override;

	// Componente de Salud (NECESITA UPROPERTY para Recoleccion de Basura)
	UPROPERTY()
	UComponenteSalud* ComponenteSalud;

	// Variables C++ puras para IA
	float VelocidadPatrulla;
	float DireccionActual;

	// Callbacks (Necesitan UFUNCTION para el sistema de delegados/colision)
	UFUNCTION()
	void AlEnemigoMorir();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void InvertirDireccion();
};