// RUTA: Source/DonkeyKongDeluxe/Private/Componentes/ComponenteInventario.cpp

#include "Componentes/ComponenteInventario.h"

UComponenteInventario::UComponenteInventario()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Inicializamos todas las variables C++
	ConteoBananas = 0;
	Vidas = 3; // El GameMode ya no necesita llevar la cuenta
	ConteoLetrasKONG = 0;
}

void UComponenteInventario::BeginPlay()
{
	Super::BeginPlay();

	// Notificar al HUD del valor inicial de ambos
	EnBananasCambiadas.Broadcast(ConteoBananas);
	EnVidasCambiadas.Broadcast(Vidas);
}

void UComponenteInventario::GanarVida()
{
	Vidas++;
	UE_LOG(LogTemp, Warning, TEXT("¡1-UP! Vidas restantes: %d"), Vidas);

	// Notificar al HUD que las vidas cambiaron
	EnVidasCambiadas.Broadcast(Vidas);
}

void UComponenteInventario::AnadirBanana()
{
	ConteoBananas++;
	UE_LOG(LogTemp, Warning, TEXT("Banana recogida! Total: %d"), ConteoBananas);
	EnBananasCambiadas.Broadcast(ConteoBananas);

	// (NUEVA LÓGICA 1-UP) [cite: 32]
	if (ConteoBananas >= 5)
	{
		ConteoBananas = 0; // Reiniciamos el contador
		EnBananasCambiadas.Broadcast(ConteoBananas); // Notificamos al HUD el reseteo
		GanarVida();
	}
}

void UComponenteInventario::AnadirLetraKONG()
{
	ConteoLetrasKONG++;
	UE_LOG(LogTemp, Warning, TEXT("Letra KONG recogida! Total: %d"), ConteoLetrasKONG);
	// (TAREA FUTURA: Notificar al HUD del cambio de letras si es necesario)

	// (NUEVA LÓGICA 1-UP) 
	if (ConteoLetrasKONG >= 4)
	{
		ConteoLetrasKONG = 0; // Reiniciamos el contador
		GanarVida();
	}
}