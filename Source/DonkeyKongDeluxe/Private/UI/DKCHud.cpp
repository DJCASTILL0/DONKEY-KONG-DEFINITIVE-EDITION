// RUTA: Source/DonkeyKongDeluxe/Private/UI/DKCHud.cpp

// DKCHud.h DEBE ser el primer include
#include "UI/DKCHud.h" 

// Includes del Proyecto
#include "Componentes/ComponenteSalud.h"
#include "Componentes/ComponenteInventario.h" 
#include "Personaje/DKCPlayerCharacter.h" 

// Includes del Motor
#include "Components/TextBlock.h" // Necesario para UTextBlock
#include "Internationalization/Text.h" // Necesario para FText
#include "Kismet/GameplayStatics.h" // Necesario para GetPlayerCharacter

void UDKCHud::NativeConstruct()
{
	Super::NativeConstruct();

	// 1. Obtener el Personaje Jugador
	// Usamos GetPlayerCharacter(0) para obtener el primer jugador.
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Si no encontramos al jugador, no podemos continuar.
	if (!Jugador)
	{
		UE_LOG(LogTemp, Error, TEXT("UDKCHud::NativeConstruct - ¡No se pudo encontrar DKCPlayerCharacter!"));
		return;
	}

	// 2. --- Vincular Componente de Salud ---
	ComponenteSaludObservado = Jugador->GetComponenteSalud();
	if (ComponenteSaludObservado)
	{
		// Suscribimos nuestra funcion C++ al delegado del componente
		ComponenteSaludObservado->EnSaludCambiada.AddDynamic(this, &UDKCHud::AlSaludCambiar);

		// Actualizamos el valor inicial del HUD
		ActualizarTextoSalud(ComponenteSaludObservado->GetSaludActual());
	}

	// 3. --- Vincular Componente de Inventario ---
	ComponenteInventarioObservado = Jugador->GetComponenteInventario();
	if (ComponenteInventarioObservado)
	{
		// Suscribimos al delegado de Bananas
		ComponenteInventarioObservado->EnBananasCambiadas.AddDynamic(this, &UDKCHud::AlBananasCambiar);
		ActualizarTextoBananas(ComponenteInventarioObservado->GetConteoBananas());

		// Suscribimos al delegado de Vidas
		ComponenteInventarioObservado->EnVidasCambiadas.AddDynamic(this, &UDKCHud::AlVidasCambiar);
		ActualizarTextoVidas(ComponenteInventarioObservado->GetVidas());
	}
}

// --- Implementación de Callbacks de Salud ---

void UDKCHud::AlSaludCambiar(float SaludActual)
{
	// El delegado EnSaludCambiada nos llama, actualizamos el texto.
	ActualizarTextoSalud(SaludActual);
}

void UDKCHud::ActualizarTextoSalud(float SaludActual)
{
	// Verificamos que el BindWidget (C++) encontrara el TextBlock (Diseñador)
	if (TextoSalud)
	{
		// Creamos el texto formateado C++
		FString StringSalud = FString::Printf(TEXT("SALUD: %d"), FMath::RoundToInt(SaludActual));
		FText TextoFormateado = FText::FromString(StringSalud);

		// Lo asignamos al widget de texto
		TextoSalud->SetText(TextoFormateado);
	}
}

// --- Implementación de Callbacks de Bananas ---

void UDKCHud::AlBananasCambiar(int TotalBananas)
{
	// El delegado EnBananasCambiadas nos llama, actualizamos el texto.
	ActualizarTextoBananas(TotalBananas);
}

void UDKCHud::ActualizarTextoBananas(int TotalBananas)
{
	if (TextoBananas)
	{
		FString StringBananas = FString::Printf(TEXT("BANANAS: %d"), TotalBananas);
		FText TextoFormateado = FText::FromString(StringBananas);
		TextoBananas->SetText(TextoFormateado);
	}
}

// --- Implementación de Callbacks de Vidas ---

void UDKCHud::AlVidasCambiar(int TotalVidas)
{
	// El delegado EnVidasCambiadas nos llama, actualizamos el texto.
	ActualizarTextoVidas(TotalVidas);
}

void UDKCHud::ActualizarTextoVidas(int TotalVidas)
{
	if (TextoVidas)
	{
		FString StringVidas = FString::Printf(TEXT("VIDAS: %d"), TotalVidas);
		FText TextoFormateado = FText::FromString(StringVidas);
		TextoVidas->SetText(TextoFormateado);
	}
}