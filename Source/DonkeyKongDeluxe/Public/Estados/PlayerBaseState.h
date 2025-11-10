// RUTA: Source/DonkeyKongDeluxe/Public/Estados/PlayerBaseState.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlayerBaseState.generated.h"

class ADKCPlayerCharacter;
class AActor;

UCLASS(Abstract, BlueprintType)
class DONKEYKONGDELUXE_API UPlayerBaseState : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ADKCPlayerCharacter* Personaje;

public:
	virtual void OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia = nullptr);
	virtual void OnExit();
	virtual void TickState(float DeltaTime);

	// --- Inputs C++ ---
	virtual void ManejarInputSalto();
	virtual void ManejarInputRodar();
	virtual bool EstaAtacando() const;
	virtual void ManejarInputMoverArriba(float Valor);

	// (NUEVO) Input C++ para rotar el barril
	virtual void ManejarInputMoverDerecha(float Valor);
};