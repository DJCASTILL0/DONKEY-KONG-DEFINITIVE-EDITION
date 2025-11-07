// RUTA: Source/DonkeyKongDeluxe/Public/Personaje/DKCPlayerCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Estados/PlayerBaseState.h" 
#include "Estrategias/PlayerStrategy.h" 

// EL ARCHIVO .GENERATED.H SIEMPRE DEBE SER EL ULTIMO INCLUDE
#include "DKCPlayerCharacter.generated.h" 

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class DONKEYKONGDELUXE_API ADKCPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADKCPlayerCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camara")
	USpringArmComponent* BrazoCamara;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camara")
	UCameraComponent* CamaraSeguimiento;

	// **LOGICA DEL PERSONAJE**
	void MoverDerecha(float Valor);
	void SaltarPresionado();
	void RodarPresionado();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// **LOGICA DEL PATRON STATE**
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patron State")
	UPlayerBaseState* EstadoActual;

	// **LOGICA DEL PATRON STRATEGY**
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patron Estrategia")
	UPlayerStrategy* EstrategiaActual;

public:
	virtual void Tick(float DeltaTime) override;
	void CambiarEstado(UPlayerBaseState* NuevoEstado);
	virtual void Jump() override;

	// Funcion publica llamada por el Estado para ejecutar la accion del Roll (delegan a la Estrategia)
	void EjecutarRodarAccion();
	void SetEstrategia(TSubclassOf<UPlayerStrategy> NuevaClaseEstrategia);
	FORCEINLINE UPlayerBaseState* GetEstadoActual() const { return EstadoActual; }

	// ELIMINACION: La logica de overlap de lianas/interactuar ha sido eliminada por completo.
};