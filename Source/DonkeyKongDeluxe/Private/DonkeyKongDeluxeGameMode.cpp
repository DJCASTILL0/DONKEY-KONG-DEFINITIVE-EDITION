
#include "DonkeyKongDeluxeGameMode.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


#include "Personaje/DKCPlayerController.h"
#include "GameFramework/HUD.h"
ADonkeyKongDeluxeGameMode::ADonkeyKongDeluxeGameMode()
{
	// 1. Asignamos el personaje C++ por defecto
	DefaultPawnClass = ADKCPlayerCharacter::StaticClass();
	VidasActuales = 3;

	
	PlayerControllerClass = ADKCPlayerController::StaticClass();


	HUDClass = AHUD::StaticClass();

	// (Aseg?rate de que no haya FClassFinder para el HUD aqu?)
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