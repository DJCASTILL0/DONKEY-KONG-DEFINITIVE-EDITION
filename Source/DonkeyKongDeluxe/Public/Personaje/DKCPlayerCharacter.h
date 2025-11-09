// RUTA: Source/DonkeyKongDeluxe/Public/Personaje/DKCPlayerCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DKCPlayerCharacter.generated.h" 

// Declaraciones anticipadas
class USpringArmComponent;
class UCameraComponent;
class UPlayerBaseState;
class UPlayerStrategy;
class UComponenteSalud;
class UDKCHud;
class UComponenteInventario;

UCLASS()
class DONKEYKONGDELUXE_API ADKCPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADKCPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void Jump() override;
	void CambiarEstado(UPlayerBaseState* NuevoEstado);
	void EjecutarRodarAccion();
	void SetEstrategia(TSubclassOf<UPlayerStrategy> NuevaClaseEstrategia);
	FORCEINLINE UComponenteSalud* GetComponenteSalud() const { return ComponenteSalud; }
	FORCEINLINE UComponenteInventario* GetComponenteInventario() const { return ComponenteInventario; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Componentes (Necesitan UPROPERTY para Recoleccion de Basura)
	UPROPERTY()
	USpringArmComponent* BrazoCamara;
	UPROPERTY()
	UCameraComponent* CamaraSeguimiento;
	UPROPERTY()
	UComponenteSalud* ComponenteSalud;
	UPROPERTY()
	UComponenteInventario* ComponenteInventario;
	// Patrones (Necesitan UPROPERTY para Recoleccion de Basura)
	UPROPERTY()
	UPlayerBaseState* EstadoActual;
	UPROPERTY()
	UPlayerStrategy* EstrategiaActual;


	// Logica de Personaje
	void MoverDerecha(float Valor);
	void SaltarPresionado();
	void RodarPresionado();

	// Callbacks (Necesitan UFUNCTION para delegados y colisiones)
	UFUNCTION()
	void AlJugadorMorir();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};