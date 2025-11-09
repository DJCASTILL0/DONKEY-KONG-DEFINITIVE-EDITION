// RUTA: Source/DonkeyKongDeluxe/Private/DonkeyKongDeluxeGameMode.cpp
#include "DonkeyKongDeluxeGameMode.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// (NUEVO) Incluimos nuestro controlador C++
#include "Personaje/DKCPlayerController.h"
#include "GameFramework/HUD.h"
ADonkeyKongDeluxeGameMode::ADonkeyKongDeluxeGameMode()
{
	// 1. Asignamos el personaje C++ por defecto
	DefaultPawnClass = ADKCPlayerCharacter::StaticClass();
	VidasActuales = 3;

	// 2. (LA SOLUCIÓN)
	// Le decimos al GameMode que use nuestro Controlador C++
	PlayerControllerClass = ADKCPlayerController::StaticClass();

	// 3. (LA SOLUCIÓN)
	// Dejamos la clase HUD por defecto. Ya no la usamos.
	HUDClass = AHUD::StaticClass();

	// (Asegúrate de que no haya FClassFinder para el HUD aquí)
}
void ADonkeyKongDeluxeGameMode::JugadorMurio(AController* ControladorDelJugador)
{
	VidasActuales--;

	UE_LOG(LogTemp, Warning, TEXT("El jugador ha muerto. Vidas restantes: %d"), VidasActuales);

	if (VidasActuales <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("GAME OVER"));
		VidasActuales = 3;
		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
	}
}