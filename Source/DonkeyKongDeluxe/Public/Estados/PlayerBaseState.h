// RUTA: Source/DonkeyKongDeluxe/Public/Estados/PlayerBaseState.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlayerBaseState.generated.h"

class ADKCPlayerCharacter; // Declaracion anticipada

UCLASS(Abstract, BlueprintType)
class DONKEYKONGDELUXE_API UPlayerBaseState : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ADKCPlayerCharacter* Personaje;

public:
	// **FUNCIONES VIRTUALES (EL CONTRATO)**
	virtual void OnEnter(ADKCPlayerCharacter* PersonajeReferencia);
	virtual void OnExit();
	virtual void TickState(float DeltaTime);

	// **MANEJADORES DE INPUT**
	virtual void ManejarInputSalto();
	virtual void ManejarInputRodar();

	// La funcion ManejarInputMoverArriba ha sido eliminada.
};