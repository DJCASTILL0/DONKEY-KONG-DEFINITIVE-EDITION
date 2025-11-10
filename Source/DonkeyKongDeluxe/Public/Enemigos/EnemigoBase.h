// RUTA: Source/DonkeyKongDeluxe/Public/Enemigos/EnemigoBase.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemigoBase.generated.h"

class UComponenteSalud;

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

	UPROPERTY()
	UComponenteSalud* ComponenteSalud;

	// --- Variables C++ Puras ---
	float VelocidadPatrulla;
	float DireccionActual;

	// (NUEVO) Interruptor C++ para definir el tipo de patrulla
	bool bPatrullaSoloEnAgua;

	UFUNCTION()
	void AlEnemigoMorir();

	// (NUEVO) Callback C++ para cuando el enemigo choca con algo
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void InvertirDireccion();
};