// RUTA: Source/DonkeyKongDeluxe/Private/Componentes/ComponenteInventario.cpp

#include "Componentes/ComponenteInventario.h"

UComponenteInventario::UComponenteInventario()
{
	PrimaryComponentTick.bCanEverTick = false;
	ConteoBananas = 0;
	Vidas = 3;
	ConteoLetrasKONG = 0;
}

void UComponenteInventario::BeginPlay()
{
	Super::BeginPlay();
	EnBananasCambiadas.Broadcast(ConteoBananas);
	EnVidasCambiadas.Broadcast(Vidas);
}

void UComponenteInventario::GanarVida()
{
	Vidas++;
	UE_LOG(LogTemp, Warning, TEXT("¡1-UP! Vidas restantes: %d"), Vidas);
	EnVidasCambiadas.Broadcast(Vidas);
}

// (NUEVA FUNCIÓN PÚBLICA C++)
void UComponenteInventario::AnadirVidas(int Cantidad)
{
	for (int i = 0; i < Cantidad; ++i)
	{
		GanarVida();
	}
}

// (LÓGICA DE BANANA 1-UP MOVIDA A 'AnadirBananas')
void UComponenteInventario::AnadirBanana()
{
	AnadirBananas(1); // Llama a la nueva función
}

// (NUEVA FUNCIÓN PÚBLICA C++)
void UComponenteInventario::AnadirBananas(int Cantidad)
{
	ConteoBananas += Cantidad;
	UE_LOG(LogTemp, Warning, TEXT("Bananas recogidas! Total: %d"), ConteoBananas);
	EnBananasCambiadas.Broadcast(ConteoBananas);

	// Lógica de 1-UP
	if (ConteoBananas >= 50)
	{
		// Calculamos cuántas vidas ganó
		int VidasGanadas = FMath::FloorToInt(ConteoBananas / 50.0f);
		AnadirVidas(VidasGanadas);

		// Reiniciamos el contador (guardando el sobrante)
		ConteoBananas = ConteoBananas % 50;
		EnBananasCambiadas.Broadcast(ConteoBananas);
	}
}

void UComponenteInventario::AnadirLetraKONG()
{
	ConteoLetrasKONG++;
	UE_LOG(LogTemp, Warning, TEXT("Letra KONG recogida! Total: %d"), ConteoLetrasKONG);

	if (ConteoLetrasKONG >= 4)
	{
		ConteoLetrasKONG = 0;
		GanarVida(); // Ganar 1 vida
	}
}