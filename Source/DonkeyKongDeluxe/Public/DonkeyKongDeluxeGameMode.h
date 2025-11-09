// RUTA: Source/DonkeyKongDeluxe/Public/DonkeyKongDeluxeGameMode.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DonkeyKongDeluxeGameMode.generated.h"

UCLASS(minimalapi)
class ADonkeyKongDeluxeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADonkeyKongDeluxeGameMode();

	// Funcion publica llamada por el personaje cuando muere
	void JugadorMurio(AController* ControladorDelJugador);

protected:
	// Variable C++ pura para el contador de vidas (sin UPROPERTY)
	int VidasActuales;
};