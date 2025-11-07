// RUTA: Source/DonkeyKongDeluxe/DonkeyKongDeluxeGameMode.cpp

#include "DonkeyKongDeluxeGameMode.h"
#include "Personaje/DKCPlayerCharacter.h" // Incluimos tu nueva clase de personaje
#include "UObject/ConstructorHelpers.h"

ADonkeyKongDeluxeGameMode::ADonkeyKongDeluxeGameMode()
{
	// Deshabilitar la busqueda del Pawn de Plantilla que genera el error
	// (Generalmente es una linea que busca un Blueprint con ConstructorHelpers::FClassFinder)

	// 1. Asignar la clase C++ de nuestro personaje como el Pawn por defecto
	DefaultPawnClass = ADKCPlayerCharacter::StaticClass();

	// Opcional: Si quieres que use el Blueprint derivado de tu nuevo personaje (BP_DKCPlayerCharacter), 
	// la sintaxis sería:
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Ruta/A/Tu/BP_DKCPlayerCharacter.BP_DKCPlayerCharacter_C"));
	// if (PlayerPawnBPClass.Class != nullptr)
	// {
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }
	// PERO por ahora, usemos el C++ puro.


	// 2. Si estás usando una clase de PlayerController diferente, también puedes forzarla aquí.
	// PlayerControllerClass = APlayerController::StaticClass();
}