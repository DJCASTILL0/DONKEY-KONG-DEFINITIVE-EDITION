// RUTA: Source/DonkeyKongDeluxe/Private/Estados/PlayerBaseState.cpp

#include "Estados/PlayerBaseState.h"

void UPlayerBaseState::OnEnter(ADKCPlayerCharacter* PersonajeReferencia)
{
	Personaje = PersonajeReferencia;
}

void UPlayerBaseState::OnExit()
{
	// Logica de limpieza por defecto (vacia)
}

void UPlayerBaseState::TickState(float DeltaTime)
{
	// Logica por Tick por defecto (vacia)
}

void UPlayerBaseState::ManejarInputSalto()
{
	// Por defecto, un estado ignora el input de salto.
}

void UPlayerBaseState::ManejarInputRodar()
{
	// Por defecto, un estado ignora el input de rodar.
}