// RUTA: Source/DonkeyKongDeluxe/Public/Personaje/DKCPlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DKCPlayerController.generated.h"

class UDKCHud; // Declaración anticipada

UCLASS()
class DONKEYKONGDELUXE_API ADKCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADKCPlayerController(); // Usaremos el constructor

protected:
	// Se llama cuando el controlador se activa
	virtual void BeginPlay() override;

private:
	// Puntero C++ a la *clase* de nuestro widget (cargada desde C++)
	TSubclassOf<class UDKCHud> HUDWidgetClass;

	// Puntero a la *instancia* del widget (para Recolección de Basura)
	UPROPERTY()
	UDKCHud* HUDWidgetInstance;
};