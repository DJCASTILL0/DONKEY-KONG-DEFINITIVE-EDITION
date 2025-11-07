// RUTA: Source/DonkeyKongDeluxe/Private/Estrategias/DonkeyKongStrategy.cpp

#include "Estrategias/DonkeyKongStrategy.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Estados/EstadoRodarTierra.h" // Para transicionar al roll

void UDonkeyKongStrategy::EjecutarRodar(ADKCPlayerCharacter* PersonajeReferencia)
{
	if (PersonajeReferencia && PersonajeReferencia->GetCharacterMovement()->IsMovingOnGround())
	{
		UE_LOG(LogTemp, Warning, TEXT("Estrategia DK: Ejecutando Roll de Donkey Kong."));

		// Transicionar a EstadoRodarTierra
		PersonajeReferencia->CambiarEstado(NewObject<UEstadoRodarTierra>(PersonajeReferencia));
	}
}

void UDonkeyKongStrategy::AjustarParametrosMovimiento()
{
	if (Personaje)
	{
		// Los valores de Donkey Kong (pesado)
		Personaje->GetCharacterMovement()->MaxWalkSpeed = 500.f;
		Personaje->GetCharacterMovement()->JumpZVelocity = 650.f;
		UE_LOG(LogTemp, Warning, TEXT("Estrategia DK: Parametros de movimiento ajustados (MaxWalkSpeed: 500)"));
	}
}