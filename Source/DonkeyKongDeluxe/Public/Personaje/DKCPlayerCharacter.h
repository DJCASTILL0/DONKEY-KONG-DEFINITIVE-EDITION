// RUTA: Source/DonkeyKongDeluxe/Public/Personaje/DKCPlayerCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DKCPlayerCharacter.generated.h" 

// Declaraciones anticipadas
class USpringArmComponent;
class UCameraComponent;
class UPlayerBaseState;
class AActor;
class UPlayerStrategy;
class UComponenteSalud;
class UComponenteInventario;
class USkeletalMesh; // (NUEVO)
class UAnimBlueprint; // (NUEVO)

UCLASS()
class DONKEYKONGDELUXE_API ADKCPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADKCPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void Jump() override;
	void CambiarEstado(UPlayerBaseState* NuevoEstado, AActor* ActorReferencia = nullptr);
	void EjecutarRodarAccion();
	void SetEstrategia(TSubclassOf<UPlayerStrategy> NuevaClaseEstrategia);

	FORCEINLINE UComponenteSalud* GetComponenteSalud() const { return ComponenteSalud; }
	FORCEINLINE UComponenteInventario* GetComponenteInventario() const { return ComponenteInventario; }

	// (NUEVO) Getters C++ para que las Estrategias accedan a las mallas
	FORCEINLINE USkeletalMesh* GetMallaDonkey() const { return MallaDonkey; }
	FORCEINLINE TSubclassOf<UAnimInstance> GetAnimClassDonkey() const { return AnimClassDonkey; }
	FORCEINLINE USkeletalMesh* GetMallaDiddy() const { return MallaDiddy; }
	FORCEINLINE TSubclassOf<UAnimInstance> GetAnimClassDiddy() const { return AnimClassDiddy; }
	FORCEINLINE USpringArmComponent* GetBrazoCamara() const { return BrazoCamara; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;

	// --- Componentes ---
	UPROPERTY()
	USpringArmComponent* BrazoCamara;
	UPROPERTY()
	UCameraComponent* CamaraSeguimiento;
	UPROPERTY()
	UComponenteSalud* ComponenteSalud;
	UPROPERTY()
	UComponenteInventario* ComponenteInventario;

	// --- Patrones ---
	UPROPERTY()
	UPlayerBaseState* EstadoActual;
	UPROPERTY()
	UPlayerStrategy* EstrategiaActual;

	// (NUEVO) Assets C++ para las mallas
	UPROPERTY()
	USkeletalMesh* MallaDonkey;
	UPROPERTY()
	TSubclassOf<UAnimInstance> AnimClassDonkey;
	UPROPERTY()
	USkeletalMesh* MallaDiddy;
	UPROPERTY()
	TSubclassOf<UAnimInstance> AnimClassDiddy;

	// --- Lógica de Personaje ---
	void MoverDerecha(float Valor);
	void SaltarPresionado();
	void RodarPresionado();
	void MoverArriba(float Valor);
	void CambiarPersonajePresionado(); // (NUEVO)

	// --- Callbacks (Funciones de Evento C++) ---
	UFUNCTION()
	void AlJugadorMorir();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};